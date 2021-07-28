//
// main.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include <server/Server.h>
#include <client/ClientPool.h>
#include <boost/thread.hpp>

int main() {
    boost::thread_group threadGroup;
    std::vector<std::shared_ptr<boost::asio::io_context>> io_contexts;

    // Server run
    Server::run(io_contexts);

    // Client run
    //ClientPool::add(io_contexts, "testnet-seed.bitcoin.jonasschnelli.ch", 18333);
    ClientPool::add(io_contexts, "host.docker.internal", 18333);


    for(const std::shared_ptr<boost::asio::io_context>& io_context_client : io_contexts){
        threadGroup.create_thread([io_context_client] { io_context_client->run(); });
    }

    threadGroup.join_all();

    return 0;
}