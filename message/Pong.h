//
// Pong.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_PONG_H
#define SHAULA_PONG_H

#include <vector>
#include "Message.h"
#include "Define.h"

class Pong : public Message{
    std::vector<unsigned char> nonce_;

public:
    explicit Pong(){
        setCommand(Command.PONG);
        setNonce();
    }

    Pong(const std::vector<unsigned char> &bytes){
        setCommand(Command.PONG);
        setNonce(bytes);
    }

    void setNonce();
    void setNonce(const std::vector<unsigned char> &bytes);
    std::vector<unsigned char> getMessage() override;
};


#endif //SHAULA_PONG_H
