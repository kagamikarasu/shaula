//
// Client.cpp
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
    if(!socket_->is_open()){
        try {
            setRunThreadId();
            _connect(yield);
        }catch (std::exception& e){
            close();
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
    try{
        boost::asio::spawn(io_context_, [this](auto && PH1) { _receive(std::forward<decltype(PH1)>(PH1)); });
    }catch(std::exception& e){
        // verification required
        close();
        return;
    }
    setAddr();
}

void Client::_receive(const boost::asio::yield_context& yield){
    std::unique_ptr<Header> header;
    std::vector<unsigned char> body;
    // Receive
    try {
        header = getHeader(yield);
        last_receive_header_ = std::make_shared<Header>(*header);
        body = getBody(yield, *header);
    }catch(std::exception& e){
        // verification required
        close();
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

    // Store the first byte for browsing.
    std::unique_ptr body_ptr = std::make_unique<Message>(*header, body);
    last_receive_body_head_ = body_ptr->getBodyHeadBytes();

    _receive(yield);
}

std::shared_ptr<Header> Client::getLastReceiveHeader(){
    if(!last_receive_header_){
        return std::make_shared<Header>();
    }
    return last_receive_header_;
}

std::string Client::getLastReceiveBodyHead() {
    std::ostringstream body_head_stream;
    for (auto v : last_receive_body_head_) {
        body_head_stream << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << (int)v;
    }
    return body_head_stream.str();
}

void Client::close(){
    Node::close();
    ClientPool::pullUp(io_context_, address_);
}