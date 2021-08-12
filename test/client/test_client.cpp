//
// test_client.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include <iostream>
#include <message/pong.h>
#include "server/server.h"
#include "client/client.h"
#include "client/resolver.h"

class ListenerTest : public ListenerIF {
private:
    bool is_version_success = false;
    bool is_verack_success = false;
    bool is_getaddr_success = false;
    bool is_pong_success = false;

public:
    explicit ListenerTest(
            NodeStruct &node_struct) :
            ListenerIF(node_struct){
    }

    void executor(Header &header, std::vector<unsigned char> &body, const boost::asio::yield_context &yield) override {
        printf("%s\n", header.getCommand().c_str());

        if(header.isVersion()){
            auto version = std::make_unique<Version>(body);
            is_version_success = true;
        }

        if(header.isVerack()){
            auto verack = std::make_unique<Message>(header, body);
            is_verack_success = true;
        }

        if(header.isGetAddr()){
            auto verack = std::make_unique<Message>(header, body);
            is_getaddr_success = true;
        }

        if(header.isPong()){
            auto pong = std::make_unique<Pong>(body);
            is_pong_success = true;
            socket_.close();

            assert(is_version_success);
            assert(is_verack_success);
            assert(is_getaddr_success);
            assert(is_pong_success);
        }
    }
};

int main(){
    // Conf
    Config::setConfig("test");

    // Accept Side
    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::acceptor ac = boost::asio::ip::tcp::acceptor(
            ioContext,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),18333)
            );
    auto s = std::make_unique<Session>(ioContext, ac);
    s->is_session_re_run_ = false;

    // Accept Test Listener
    NodeStruct ns = s->getStruct();
    s->addListener(std::make_unique<ListenerTest>(ns));

    // Client Side
    auto v6address = Resolver::getAddresses("host.docker.internal")[0];
    auto c = std::make_unique<Client>(ioContext, v6address, 18333);
    c->run();

    ioContext.run();

    return 0;
}