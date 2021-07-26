//
// Server.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "Server.h"

Server::Server(boost::asio::io_context &io_context) : acceptor_(std::make_unique<boost::asio::ip::tcp::acceptor>(boost::asio::ip::tcp::acceptor(io_context,
                                                                                                   boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 18333))))
                                                      {
    for(int i= 0 ; i < 10 ; ++i){
        sessions_.push_back(std::make_unique<Session>(io_context, *acceptor_));
    }
}

void Server::run(){
    for (int i = 0; i < 10 ; ++i) {
        sessions_[i]->run();
    }
}