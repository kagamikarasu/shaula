//
// Mempool.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_MEMPOOL_H
#define SHAULA_MEMPOOL_H

#include <vector>
#include "message.h"

/**
 * Create a Mempool request.
 * Mempool is an empty payload.
 */
class Mempool : public Message{
public:
    explicit Mempool();
};


#endif //SHAULA_MEMPOOL_H
