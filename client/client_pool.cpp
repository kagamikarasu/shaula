//
// ClientPool.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "client_pool.h"

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

    std::lock_guard<std::mutex> lock(clientPool->locker_);

    for(auto endpoint : endpoint_list){
        if(clientPool->connection_pool_.find(endpoint.getAddressString()) != clientPool->connection_pool_.end()){
            continue;
        }
        clientPool->_addUPool(endpoint.getAddressV6().to_string(), endpoint.getPort());
    }
}

void ClientPool::run(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts){
    ClientPool* clientPool = getInstance();
    size_t cs_io_ctx = io_contexts.size();

    // Make sure to place at least one in a thread.
    for(int t = 0 ; t < number_of_thread_ ; ++t){
        std::shared_ptr<boost::asio::io_context> io_context = std::make_shared<boost::asio::io_context>();
        io_contexts.push_back(io_context);
    }

    // Only io_context created by this
    for (; cs_io_ctx < io_contexts.size(); ++cs_io_ctx) {
        clientPool->_pullUp(*io_contexts.at(cs_io_ctx));
    }
}

void ClientPool::close(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address){
    ClientPool* clientPool = getInstance();

    std::lock_guard<std::mutex> lock(clientPool->locker_);

    clientPool->_removeCPool(io_context, address);
}

void ClientPool::pullUp(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address){
    ClientPool* clientPool = getInstance();

    // If it is locked in another thread, wait the specified time and check again.
    std::lock_guard<std::mutex> lock(clientPool->locker_);

    // Remove from connected list
    clientPool->_removeCPool(io_context, address);

    // Add From connected pool, Delete From unused pool.
    clientPool->_pullUp(io_context);
}

void ClientPool::resize(boost::asio::io_context &io_context){
    ClientPool* clientPool = getInstance();

    std::lock_guard<std::mutex> lock(clientPool->locker_);

    clientPool->_pullUp(io_context);
}

void ClientPool::_addUPool(const std::string &address, uint16_t port){
    unused_pool_.insert(std::make_pair( address, port));
}

void ClientPool::_addCPool(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address, uint16_t port){
    connection_pool_.insert(std::make_pair(address.to_string(), Client(io_context, address, port)));
    connection_pool_.at(address.to_string()).run();

    if(!thread_connection_manager_.contains(&io_context)){
        thread_connection_manager_.insert(std::make_pair(&io_context, 0));
    }
    ++thread_connection_manager_.at(&io_context);
}

void ClientPool::_pullUp(boost::asio::io_context &io_context) {

    for(int cpt = 0 ; cpt < client_per_thread ; ++cpt) {
        if(unused_pool_.empty()){
            break;
        }

        if(thread_connection_manager_.find(&io_context)->second >= client_per_thread){
            break;
        }

        auto itb = unused_pool_.begin();

        boost::asio::ip::address_v6 v6_address = boost::asio::ip::make_address_v6(itb->first);
        _addCPool(io_context, v6_address, itb->second);

        unused_pool_.erase(itb);
    }
}

void ClientPool::_removeCPool(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address){
    auto itd = connection_pool_.find(address.to_string());
    connection_pool_.erase(itd);
    --thread_connection_manager_.at(&io_context);
}

void ClientPool::_emptyPoolBlock(){
    while(true){
        if(!unused_pool_.empty()){
            break;
        }
        sleep(1);
    }
}

std::map<std::string, Client> ClientPool::getConnectionList(){
    return getInstance()->connection_pool_;
}