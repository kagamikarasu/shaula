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
    run();
}

void Session::run(){
    boost::asio::spawn(io_context_, [this](auto && PH1) { accept(std::forward<decltype(PH1)>(PH1)); });
}

void Session::accept(const boost::asio::yield_context &yield){
    _set_run_thread_id();

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
        version_ = std::make_shared<Version>(body);
        sendVersion(yield);
        sendVerack(yield);
        sendPing(yield);
    }

    // getaddr
    if(header->isGetAddr()){
        sleep(10);
        close();
        return;
    }

    // Mempool
    if(header->isMempool()){
        close();
        return;
    }

    receive(yield);
}

std::string Session::getAddress(){
    return endpoint_.remote_address.to_string();
}

std::shared_ptr<Version> Session::getVersion(){
    if(!version_){
        return std::make_shared<Version>();
    }
    return version_;
}

std::string Session::getRunThreadId(){
    return run_thread_id_;
}

void Session::_set_run_thread_id(){
    std::ostringstream thread_id_stream;
    thread_id_stream << boost::this_thread::get_id();
    run_thread_id_ = thread_id_stream.str();
}

bool Session::isOpen(){
    return socket_->is_open();
}

void Session::close(){
    socket_->close();
    run();
}