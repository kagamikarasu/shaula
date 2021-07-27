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

int main() {
    boost::asio::io_context ioContext;

    // Listen run
    std::unique_ptr<Server> s = std::make_unique<Server>(ioContext);
    s->run();

    // Client run
    //ClientPool::add(ioContext, "testnet-seed.bitcoin.jonasschnelli.ch", 18333);
    ClientPool::add(ioContext, "host.docker.internal", 18333);

    ioContext.run();

    return 0;
}