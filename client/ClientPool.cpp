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

ClientPool& ClientPool::getInstance(){
    static ClientPool clientPool;
    return clientPool;
}

void ClientPool::add(boost::asio::io_context &io_context, const std::string &dns_address, uint16_t port) {
    std::vector<boost::asio::ip::address_v6> v6_addresses = Resolver::getAddresses(io_context, dns_address);
    for(const auto& v6_address : v6_addresses){
        add(io_context, v6_address, port);
    }
}

void ClientPool::add(boost::asio::io_context &io_context, std::vector<NetAddr> endpoint_list) {
    for(auto endpoint : endpoint_list){
        add(io_context, endpoint.getAddressV6(), endpoint.getPort());
    }
}

void ClientPool::add(boost::asio::io_context &io_context, const boost::asio::ip::address_v6 &address, uint16_t port){
    // Check if node is already connected
    if(getInstance().connection_pool_.find(address.to_string()) != getInstance().connection_pool_.end()){
        return;
    }

    // Check maximum number of connections
    if(isMaxConnection()){
        auto result = getInstance().unused_pool_.insert(std::make_pair( address.to_string(), port));
        return;
    }

    // Add connection
    auto result = getInstance().connection_pool_.insert(std::make_pair(address.to_string(), Client(io_context, address, port)));

    // Run current connection
    if(result.second) {
        _run(address.to_string());
    }
}

void ClientPool::_run(const std::string &address){
    getInstance().connection_pool_.at(address).run();
}

void ClientPool::resize(boost::asio::io_context &io_context){
    // Delete Client from ConnectionPool
    auto itd = getInstance().connection_pool_.begin();
    while (itd != getInstance().connection_pool_.end()) {
        if (!itd->second.isOpen()) {
            getInstance().connection_pool_.erase(itd++);
        } else ++itd;
    }

    // Add ConnectionPool from UnusedPool
    auto ita = getInstance().unused_pool_.begin();
    while(ita != getInstance().unused_pool_.end()){
        if(isMaxConnection()){
            return;
        }
        boost::asio::ip::address_v6 v6_address = boost::asio::ip::make_address_v6(ita->first);
        add(io_context, v6_address, ita->second);
        getInstance().unused_pool_.erase(ita++);
    }
}

bool ClientPool::isMaxConnection(){
    if(getInstance().connection_pool_.size() >= 10){
        return true;
    }
    return false;
}