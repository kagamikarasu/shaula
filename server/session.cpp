//
// Session.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "session.h"

Session::Session(boost::asio::io_context &ioContext, boost::asio::ip::tcp::acceptor &acceptor) :
    Node(ioContext),
    acceptor_(acceptor){
    setDefaultListener();
    run();
}

void Session::run(){
    boost::asio::spawn(io_context_, [this](auto && PH1) { accept(std::forward<decltype(PH1)>(PH1)); });
}

void Session::accept(const boost::asio::yield_context &yield){
    setRunThreadId();

    acceptor_.async_accept(socket_, yield);

    endpoint_.set(socket_);

    receive(yield);
}

void Session::receive(const boost::asio::yield_context &yield){
    std::shared_ptr<Header> header;
    std::vector<unsigned char> body;

    // Receive
    try {
        header = std::move(getHeader(yield));
        body = std::move(getBody(yield, *header));
    }catch(std::exception& e){
        if(!is_session_re_run_){
            Node::close();
            return;
        }
        Session::close();
        return;
    }

    // Listener
    for(const auto& gl : listeners_){
        gl->executor(*header, body, yield);
    }

    last_recv_.setHeader(*header);

    receive(yield);
}

std::string Session::getAddress(){
    return endpoint_.remote_address.to_string();
}

void Session::close(){
    Node::close();
    run();
}