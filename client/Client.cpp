//
// Client.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include <boost/thread.hpp>
#include "Client.h"
#include "ClientPool.h"

Client::Client(boost::asio::io_context &io_context, boost::asio::ip::address_v6 address, uint16_t port) :
    Node(io_context),
    address_(std::move(address)),
    port_(port){
}

void Client::run(){
    boost::asio::spawn(io_context_, [this](auto && PH1) { _run(std::forward<decltype(PH1)>(PH1)); });
}

void Client::_run(const boost::asio::yield_context &yield){
    if(!socket_->is_open()){
        try {
            _connect(yield);
        }catch (std::exception& e){
            _close();
            return;
        }
    }

    sendVersion(yield);
}

void Client::_connect(const boost::asio::yield_context &yield){
    if(socket_->is_open()) {
        return;
    }

    // Async Connect
    socket_->async_connect(boost::asio::ip::tcp::endpoint(address_, port_), yield);

    boost::asio::socket_base::keep_alive option(false);
    socket_->set_option(option);

    // Receiver
    boost::asio::spawn(io_context_, [this](auto && PH1) { _receive(std::forward<decltype(PH1)>(PH1)); });
    setAddr();
}

void Client::_receive(const boost::asio::yield_context& yield){
    std::unique_ptr<Header> header;
    std::vector<unsigned char> body;
    // Receive
    try {
        header = getHeader(yield);
        last_message_header_ = std::make_shared<Header>(*header);
        body = getBody(yield, *header);
    }catch(std::exception& e){
        _close();
        return;
    }

    // version
    if(header->isVersion()){
        version_ = std::make_shared<Version>(body);
    }

    // verack
    if(header->isVerack()){
        sendVerack(yield);
        sendGetAddr(yield);
    }

    // addr
    if(header->isAddr()){
        std::unique_ptr<Addr> addr = std::make_unique<Addr>(body);
        std::vector<NetAddr> addr_list = addr->getAddrList();
        ClientPool::add(io_context_, addr_list);
    }

    // ping
    if(header->isPing()){
        std::unique_ptr<Ping> ping = std::make_unique<Ping>(body);
        sendPong(yield, ping->getNonce());
    }

    _receive(yield);
}

bool Client::isOpen(){
    return socket_->is_open();
}

std::shared_ptr<Version> Client::getVersion(){
    if(!version_){
        return std::make_shared<Version>();
    }
    return version_;
}

std::shared_ptr<Header> Client::getLastReceiveHeader(){
    if(!last_message_header_){
        return std::make_shared<Header>();
    }
    return last_message_header_;
}

void Client::_close(){
    socket_->close();
    ClientPool::pullUp(io_context_, address_);
}