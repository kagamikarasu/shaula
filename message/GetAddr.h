//
// GetAddr.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_GETADDR_H
#define SHAULA_GETADDR_H

#include "Message.h"

class GetAddr : public Message {
public:
    explicit GetAddr(){
        setCommand(Command.GETADDR);
    }
};


#endif //SHAULA_GETADDR_H
