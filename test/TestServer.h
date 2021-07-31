//
// TestServer.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_TESTSERVER_H
#define SHAULA_TESTSERVER_H

#include "server/Server.h"

class TestServer {
    void testTenConnection(){
        boost::thread_group threadGroup;
        std::vector<std::shared_ptr<boost::asio::io_context>> io_contexts;

        Server::run(io_contexts);

        std::shared_ptr<boost::asio::io_context> ioContext = std::make_shared<boost::asio::io_context>();
        std::vector<std::shared_ptr<Client>> vc;
        for(int i = 0 ; i < 10 ; i++){
            auto c= std::make_shared<Client>(*ioContext, boost::asio::ip::make_address_v6("::ffff:192.168.65.2"), 18333);
            c->run();
            vc.push_back(c);
        }
        io_contexts.push_back(ioContext);

        for(const std::shared_ptr<boost::asio::io_context>& io_context_client : io_contexts){
            threadGroup.create_thread([io_context_client] { io_context_client->run(); });
        }

        threadGroup.join_all();
    }
};


#endif //SHAULA_TESTSERVER_H
