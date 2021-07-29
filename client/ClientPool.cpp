//
// ClientPool.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "ClientPool.h"

ClientPool* ClientPool::getInstance(){
    static ClientPool clientPool;
    return &clientPool;
}

void ClientPool::add(const std::string &dns_address, uint16_t port) {
    ClientPool* clientPool = getInstance();

    // Name resolution
    std::vector<boost::asio::ip::address_v6> v6_addresses = Resolver::getAddresses(dns_address);

    for(const auto& v6_address : v6_addresses){
        if(clientPool->connection_pool_.find(v6_address.to_string()) != clientPool->connection_pool_.end()){
            continue;
        }
        clientPool->_addUPool(v6_address.to_string(), port);
    }
}

void ClientPool::add(boost::asio::io_context &io_context, const std::vector<NetAddr> &endpoint_list) {
    ClientPool* clientPool = getInstance();
    for(auto endpoint : endpoint_list){
        if(clientPool->connection_pool_.find(endpoint.getAddressString()) != clientPool->connection_pool_.end()){
            continue;
        }
        clientPool->_addUPool(endpoint.getAddressV6().to_string(), endpoint.getPort());
    }
}

void ClientPool::run(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts){
    ClientPool* clientPool = getInstance();

    for(int t = 0 ; t < number_of_thread_ ; ++t){
        std::shared_ptr<boost::asio::io_context> io_context = std::make_shared<boost::asio::io_context>();
        clientPool->_pullUp(*io_context);
        io_contexts.push_back(io_context);

        if(clientPool->unused_pool_.empty()){
            break;
        }
    }
}

void ClientPool::pullUp(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address){
    ClientPool* clientPool = getInstance();

    // If it is locked in another thread, wait the specified time and check again.
    clientPool->_lock();

    // Remove from connected list
    clientPool->_removeCPool(address);

    // If empty from unused list, wait for another thread to get it.
    clientPool->_emptyPoolBlock();

    // Add From connected pool, Delete From unused pool.
    clientPool->_pullUp(io_context);

    // unlock
    clientPool->_unlock();
}

void ClientPool::_addUPool(const std::string &address, uint16_t port){
    unused_pool_.insert(std::make_pair( address, port));
}

void ClientPool::_addCPool(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address, uint16_t port){
    connection_pool_.insert(std::make_pair(address.to_string(), Client(io_context, address, port)));
    connection_pool_.at(address.to_string()).run();
}

void ClientPool::_pullUp(boost::asio::io_context &io_context){
    auto itb = unused_pool_.begin();

    boost::asio::ip::address_v6 v6_address = boost::asio::ip::make_address_v6(itb->first);
    _addCPool(io_context, v6_address, itb->second);

    unused_pool_.erase(itb);
}

void ClientPool::_removeCPool(const boost::asio::ip::address_v6 &address){
    auto itd = connection_pool_.find(address.to_string());
    connection_pool_.erase(itd);
}

void ClientPool::_emptyPoolBlock(){
    while(true){
        if(!unused_pool_.empty()){
            break;
        }
        sleep(1);
    }
}

void ClientPool::_lock(){
    while(true) {
        if (!lock_) {
            lock_ = true;
            break;
        }
        sleep(1);
    }
}

void ClientPool::_unlock(){
    lock_ = false;
}

std::map<std::string, Client> ClientPool::getConnectionList(){
    return getInstance()->connection_pool_;
}