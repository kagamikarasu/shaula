//
// Pong.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "Pong.h"

Pong::Pong(const std::vector<unsigned char> &bytes) {
    setCommand(Command.PONG);
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
