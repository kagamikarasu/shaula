//
// Ping.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "Ping.h"

void Ping::setNonce() {
    nonce_ = Crypt::getRand(8);
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
