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
            return;
        }
    }

    Version::send(*socket_, yield, endpoint_);
}

void Client::_connect(const boost::asio::yield_context &yield){
    if(socket_->is_open()) {
        return;
    }

    // Wait time between connection and receiving Version message
    timeout_->expires_from_now(boost::posix_time::seconds(7));
    timeout_->async_wait([this](const boost::system::error_code &ec) {
        // An error occurs if you cancel.(timeout)
        if (!ec || version_ == nullptr) {
            Client::close();
            return;
        }
    });

    // Async Connect
    socket_->async_connect(boost::asio::ip::tcp::endpoint(address_, port_), yield);

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
        last_receive_header_ = std::make_shared<Header>(*header);
        body = getBody(yield, *header);
    }catch(std::exception& e){
        return;
    }

    // version
    if(header->isVersion()){
        timeout_->cancel();
        version_ = std::make_shared<Version>(body);
    }

    // verack
    if(header->isVerack()){
        Verack::send(*socket_, yield);
        GetAddr::send(*socket_, yield);
    }

    // addr
    if(header->isAddr()){
        ClientPool::add(io_context_, std::make_unique<Addr>(body)->getAddrList());
    }

    // ping
    if(header->isPing()){
        Pong::send(*socket_, yield, std::make_unique<Ping>(body)->getNonce());
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
    ClientPool::close(io_context_, address_);
    ClientPool::resize(io_context_);
}