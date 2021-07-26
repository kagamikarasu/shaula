//
// Mempool.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "Mempool.h"

std::vector<unsigned char> Mempool::getMessage() {
    payload_.clear();
    return Message::getMessage();
}
