//
// main.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "client/client_pool.h"
#include "server/server.h"
#include "observer/display.h"

int main() {
    boost::thread_group threadGroup;
    std::vector<std::shared_ptr<boost::asio::io_context>> io_contexts;

    // Server run
    Server::run(io_contexts);

    // Client run
    ClientPool::add("testnet-seed.bitcoin.jonasschnelli.ch", 18333);
    //ClientPool::add("host.docker.internal", 18333);
    ClientPool::run(io_contexts);

    Display::show(io_contexts);

    for(const std::shared_ptr<boost::asio::io_context>& io_context_client : io_contexts){
        threadGroup.create_thread([io_context_client] { io_context_client->run(); });
    }

    threadGroup.join_all();

    return 0;
}