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

Server::Server(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts) {
    context_server_ = std::make_shared<boost::asio::io_context>();
    acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(
            boost::asio::ip::tcp::acceptor(
                    *context_server_,
                        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),18333)
                    )
                );
}

Server* Server::getInstance(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts){
    static Server server(io_contexts);
    return &server;
}

void Server::run(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts){
    Server* server = getInstance(io_contexts);

    // Number of simultaneous connections
    for(int i= 0 ; i < 10 ; ++i){
        server->sessions_.push_back(std::make_unique<Session>(*server->context_server_, *server->acceptor_));
    }
    // Number of Threads
    for(int i= 0 ; i < 10 ; ++i){
        io_contexts.push_back(server->context_server_);
    }
}