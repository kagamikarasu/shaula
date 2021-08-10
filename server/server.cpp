//
// Server.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "server.h"

Server::Server() {
    context_server_ = std::make_shared<boost::asio::io_context>();
    acceptor_ = std::make_unique<boost::asio::ip::tcp::acceptor>(
            boost::asio::ip::tcp::acceptor(
                    *context_server_,
                        boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),18333)
                    )
                );
}

Server* Server::getInstance(){
    static Server server;
    return &server;
}

void Server::run(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts){
    Server* server = getInstance();

    // Number of simultaneous connections
    for(int i= 0 ; i < max_connections_ ; ++i){
        std::shared_ptr<Session> session = std::move(
                std::make_unique<Session>(*server->context_server_, *server->acceptor_));
        server->sessions_.push_back(session);
    }
    // Number of Threads
    for(int i= 0 ; i < number_of_thread_ ; ++i){
        io_contexts.push_back(server->context_server_);
    }
}

std::vector<Session*> Server::getConnectionList() {
    Server* server = getInstance();
    std::vector<Session*> stc_open;
    for(const auto& s : server->sessions_){
        if(s->isOpen()){
            stc_open.push_back(&*s);
        }
    }
    return stc_open;
}
