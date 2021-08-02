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
#include "config/config.h"

int main() {
    boost::thread_group threadGroup;
    std::vector<std::shared_ptr<boost::asio::io_context>> io_contexts;

    // Config
    Config::setConfig("main");

    // Server run
    Server::run(io_contexts);

    // Client Preparation
    // ClientPool::add("testnet-seed.bitcoin.jonasschnelli.ch", 18333);
    ClientPool::add("host.docker.internal", 18333);
    // ClientPool::add("seed.bitcoinstats.com", 8333);
    // ClientPool::add("dnsseed.bluematt.me", 8333);

    // Client run
    ClientPool::run(io_contexts);

    Display::show(io_contexts);

    for(const std::shared_ptr<boost::asio::io_context>& io_context_client : io_contexts){
        threadGroup.create_thread([io_context_client] { io_context_client->run(); });
    }

    threadGroup.join_all();

    return 0;
}