//
// Ping.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "ping.h"

Ping::Ping() {
    setCommand(CommandDef.PING);
    setNonce();
}

Ping::Ping(const std::vector<unsigned char> &bytes) {
    setNonce(bytes);
}

void Ping::setNonce() {
    nonce_ = Crypt::getRandNonce(8);
}

void Ping::setNonce(const std::vector<unsigned char> &bytes) {
    nonce_ = bytes;
}

std::vector<unsigned char> Ping::getMessage() {
    std::vector<unsigned char> payload;

    payload.insert(payload.end(), nonce_.begin(), nonce_.end());

    Message::setPayload(payload);

    return Message::getMessage();
}

std::vector<unsigned char> Ping::getNonce() {
    return nonce_;
}

void Ping::send(
        boost::asio::ip::tcp::socket &socket,
        const boost::asio::yield_context &yield,
        LastSend& last_send){
    auto v = std::make_unique<Ping>();
    v->sendMessage(socket, yield);

    last_send.setHeader(v->getHeader());
}