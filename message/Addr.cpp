//
// Addr.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "Addr.h"

void Addr::setAddrList(const std::vector<unsigned char> &bytes){

    uint8_t read_position = var_int_->getPosition();

    for(int i = 0 ; i < var_int_->getLength() ; ++i){
        std::vector<unsigned char> addr_vec = {&bytes[read_position + (i * 30)] , &bytes[read_position + (i * 30) + 30]};
        std::unique_ptr<NetAddr> net_addr = std::make_unique<NetAddr>(addr_vec);

        addrList_.push_back(*net_addr);
    }
}

void Addr::showAddrList(){
    for(NetAddr addr : addrList_){
        std::printf("%s\n", addr.getAddressString().c_str());
    }
}

std::vector<NetAddr> Addr::getAddrList() {
    return addrList_;
}
