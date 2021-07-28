//
// Session.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#include <boost/thread.hpp>
#include "Session.h"

Session::Session(boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &acceptor) :
    Node(ioContext),
    acceptor_(acceptor){
    run();
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
        return;
    }

    // Mempool
    if(header->isMempool()){
        close();
        return;
    }

    auto message = new Message(*header, body);

    std::ostringstream oss;
    oss << boost::this_thread::get_id();
    printf("(%s) - Server Receive Message:", oss.str().c_str());

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