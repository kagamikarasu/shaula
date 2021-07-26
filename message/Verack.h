//
// Verack.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_VERACK_H
#define SHAULA_VERACK_H

#include "Message.h"

class Verack : public Message{
public:
    explicit Verack(){
        setCommand(Command.VERACK);
    };
};


#endif //SHAULA_VERACK_H
