//
// Ping.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_PING_H
#define SHAULA_PING_H

#include <vector>
#include "Message.h"
#include "Define.h"

class Ping : public Message{
    std::vector<unsigned char> nonce_;

public:
    explicit Ping(){
        setCommand(Command.PING);
        setNonce();
    }

    Ping(const std::vector<unsigned char> &bytes){
        setNonce(bytes);
    }

    void setNonce();
    void setNonce(const std::vector<unsigned char> &bytes);

    std::vector<unsigned char> getNonce();
    std::vector<unsigned char> getMessage() override;
};


#endif //SHAULA_PING_H
