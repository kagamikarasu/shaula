//
// Pong.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "pong.h"

Pong::Pong(const std::vector<unsigned char> &bytes) {
    setCommand(CommandDef.PONG);
    setNonce(bytes);
}

void Pong::setNonce(const std::vector<unsigned char> &bytes) {
    nonce_ = bytes;
}

std::vector<unsigned char> Pong::getMessage() {
    std::vector<unsigned char> payload;

    payload.insert(payload.end(), nonce_.begin(), nonce_.end());

    Message::setPayload(payload);

    return Message::getMessage();
}

void Pong::send(
        boost::asio::ip::tcp::socket &socket,
        const boost::asio::yield_context &yield,
        LastSend& last_send,
        const std::vector<unsigned char> &bytes) {

    auto v = std::make_unique<Pong>(bytes);
    v->sendMessage(socket, yield);

    last_send.setHeader(v->getHeader());
}