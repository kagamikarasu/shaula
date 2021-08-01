//
// Mempool.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "mempool.h"

Mempool::Mempool() {
    setCommand(Command.MEMPOOL);
}
