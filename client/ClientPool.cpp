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

void ClientPool::add(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts, const std::string &dns_address, uint16_t port) {
    // Name resolution
    std::vector<boost::asio::ip::address_v6> v6_addresses = Resolver::getAddresses(dns_address);

    // Generate io_context according to the number of connections
    for(const auto& v6_address : v6_addresses){
        std::shared_ptr<boost::asio::io_context> io_context = std::make_shared<boost::asio::io_context>();
        add(*io_context, v6_address, port);
        io_contexts.push_back(io_context);
    }
}

void ClientPool::add(boost::asio::io_context &io_context, const std::vector<NetAddr> &endpoint_list) {
    for(auto endpoint : endpoint_list){
        add(io_context, endpoint.getAddressV6(), endpoint.getPort());
    }
}

void ClientPool::add(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address, uint16_t port){
    ClientPool* clientPool = getInstance();
    // Check if node is already connected
    if(clientPool->connection_pool_.find(address.to_string()) != clientPool->connection_pool_.end()){
        return;
    }

    // Check maximum number of connections
    if(isMaxConnection()){
        auto result = clientPool->unused_pool_.insert(std::make_pair( address.to_string(), port));
        return;
    }

    // Add connection
    auto result = clientPool->connection_pool_.insert(std::make_pair(address.to_string(), Client(io_context, address, port)));

    // Run current connection
    if(result.second) {
        clientPool->_run(address.to_string());
    }
}

void ClientPool::_run(const std::string &address){
    connection_pool_.at(address).run();
}

void ClientPool::pullUp(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address){
    ClientPool* clientPool = getInstance();
    // If it is locked in another thread, wait the specified time and check again.
    while(true) {
        if (!clientPool->lock_) {
            clientPool->lock_ = true;
            break;
        }
        sleep(1);
        clientPool = getInstance();
    }

    // Remove from connected list
    auto itd = clientPool->connection_pool_.find(address.to_string());
    clientPool->connection_pool_.erase(itd);

    // If empty from unused list, wait for another thread to get it.
    while(true){
        if(!clientPool->unused_pool_.empty()){
            break;
        }
        sleep(1);
    }

    auto itb = clientPool->unused_pool_.begin();
    boost::asio::ip::address_v6 v6_address = boost::asio::ip::make_address_v6(itb->first);
    add(io_context, v6_address, itb->second);
    clientPool->unused_pool_.erase(itb);

    clientPool->lock_ = false;
}

void ClientPool::resize(boost::asio::io_context &io_context){
    ClientPool* clientPool = getInstance();

    // Removes a closed client from the connection pool.
    auto itd = clientPool->connection_pool_.begin();
    while (itd != clientPool->connection_pool_.end()) {
        if (!itd->second.isOpen()) {
            clientPool->connection_pool_.erase(itd++);
        } else ++itd;
    }

    // Promotes an unused connection pool to a connected pool.
    auto ita = clientPool->unused_pool_.begin();
    while(ita != clientPool->unused_pool_.end()){
        if(isMaxConnection()){
            return;
        }
        boost::asio::ip::address_v6 v6_address = boost::asio::ip::make_address_v6(ita->first);
        add(io_context, v6_address, ita->second);
        clientPool->unused_pool_.erase(ita++);
    }
}

std::map<std::string, Client> ClientPool::getConnectionList(){
    return getInstance()->connection_pool_;
}

bool ClientPool::isMaxConnection(){
    ClientPool* clientPool = getInstance();

    if(clientPool->connection_pool_.size() >= 10){
        return true;
    }
    return false;
}