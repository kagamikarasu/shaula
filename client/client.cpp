//
// client.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "client.h"
#include "client_pool.h"

Client::Client(boost::asio::io_context &io_context, boost::asio::ip::address_v6 address, uint16_t port) :
    Node(io_context),
    address_(std::move(address)),
    port_(port){
}

void Client::run(){
    boost::asio::spawn(io_context_, [this](auto && PH1) { _run(std::forward<decltype(PH1)>(PH1)); });
}

void Client::_run(const boost::asio::yield_context &yield){
    if(!socket_.is_open()){
        try {
            setRunThreadId();
            _connect(yield);
        }catch (std::exception& e){
            return;
        }
    }

    Version::send(socket_, yield, endpoint_);
}

void Client::_connect(const boost::asio::yield_context &yield){
    if(socket_.is_open()) {
        return;
    }

    // Wait time between connection and receiving Version message
    timeout_.expires_from_now(boost::posix_time::seconds(7));
    timeout_.async_wait([this](const boost::system::error_code &ec) {
        // An error occurs if you cancel.(timeout)
        if (!ec || !last_recv_.hasHeader()) {
            Client::close();
            return;
        }
    });

    // Async Connect
    socket_.async_connect(boost::asio::ip::tcp::endpoint(address_, port_), yield);

    // Receiver
    boost::asio::spawn(io_context_, [this](auto && PH1) { _receive(std::forward<decltype(PH1)>(PH1)); });

    setAddr();
}

void Client::_receive(const boost::asio::yield_context& yield){
    std::vector<unsigned char> body;
    // Receive
    try {
        last_recv_.setHeader(*getHeader(yield));
        body = getBody(yield, last_recv_.getHeader());
    }catch(std::exception& e){
        return;
    }

    // Listener
    for(const auto& gl : listeners_){
        gl->executor(last_recv_.getHeader(), body, yield);
    }

    // Store the first byte for browsing.
    std::unique_ptr body_ptr = std::make_unique<Message>(last_recv_.getHeader(), body);
    last_recv_.setHeadBody(body_ptr->getBodyHeadBytes());

    _receive(yield);
}

void Client::close(){
    Node::close();
    ClientPool::close(io_context_, address_);
    ClientPool::resize(io_context_);
}