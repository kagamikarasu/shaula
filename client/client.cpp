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

    Version::send(socket_, yield, last_send_, endpoint_);
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

    endpoint_.set(socket_);
}

void Client::_receive(const boost::asio::yield_context& yield){
    std::shared_ptr<Header> header;
    std::vector<unsigned char> body;
    // Receive
    try {
        header = std::move(getHeader(yield));
        body = std::move(getBody(yield, *header));
    }catch(std::exception& e){
        return;
    }

    // Listener
    for(const auto& gl : listeners_){
        gl->executor(*header, body, yield);
    }

    last_recv_.setHeader(*header);

    // Store the first byte for browsing.
    std::unique_ptr body_ptr = std::make_unique<Message>(*header, body);
    last_recv_.setHeadBody(body_ptr->getBodyHeadBytes());

    _receive(yield);
}

void Client::close(){
    Node::close();
    ClientPool::close(io_context_, address_);
    ClientPool::resize(io_context_);
}