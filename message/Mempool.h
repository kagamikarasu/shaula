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
#include "Message.h"

class Mempool : public Message{
public:
    explicit Mempool(){
        setCommand(Command.MEMPOOL);
    }
    std::vector<unsigned char> getMessage() override;
};


#endif //SHAULA_MEMPOOL_H
