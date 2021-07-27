//
// Session.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#include "Session.h"

Session::Session(boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &acceptor) :
    Node(ioContext),
    acceptor_(acceptor){
}

void Session::run(){
    boost::asio::spawn(io_context_, [this](auto && PH1) { accept(std::forward<decltype(PH1)>(PH1)); });
}

void Session::accept(const boost::asio::yield_context &yield){
    acceptor_.async_accept(*socket_, yield);
    setAddr();
    receive(yield);
}

void Session::receive(const boost::asio::yield_context &yield){
    std::unique_ptr<Header> header;
    std::vector<unsigned char> body;

    // Receive
    try {
        header = getHeader(yield);
        body = getBody(yield, *header);
    }catch(std::exception& e){
        close();
        return;
    }

    // version
    if(header->isVersion()){
        sendVersion(yield);
        sendVerack(yield);
        sendPing(yield);
    }

    // getaddr
    if(header->isGetAddr()){
        close();
    }

    // Mempool
    if(header->isMempool()){
        close();
    }

    auto message = new Message(*header, body);

    printf("Server Receive Message:");
    for(const unsigned char value : message->getMessage()) {
        printf(" %02x", value);
    }

    std::cout << std::endl;

    delete message;

    receive(yield);
}

void Session::close(){
    socket_->close();
    run();
}