//
// Addr.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_ADDR_H
#define SHAULA_ADDR_H


#include "Message.h"

class Addr : public Message {
    std::unique_ptr<VarInt> var_int_;
    std::vector<NetAddr> addrList_;

public:
    explicit Addr(const std::vector<unsigned char> &bytes){
        var_int_ = std::make_unique<VarInt>(bytes);
        setAddrList(bytes);
    }

    void setAddrList(const std::vector<unsigned char> &bytes);

    std::vector<NetAddr> getAddrList();

    void showAddrList();
};


#endif //SHAULA_ADDR_H
