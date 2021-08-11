//
// Verack.hpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "verack.h"

Verack::Verack() {
    setCommand(CommandDef.VERACK);
}

void Verack::send(
        boost::asio::ip::tcp::socket &socket,
        const boost::asio::yield_context &yield,
        LastSend& last_send) {
    auto v = std::make_unique<Verack>();
    v->sendMessage(socket, yield);

    last_send.disableVerack();
    last_send.setHeader(v->getHeader());
}