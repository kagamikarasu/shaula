//
// last_recv.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "last_recv.h"

void LastRecv::setVersion(const std::vector<unsigned char> &body){
    version_ = std::make_unique<Version>(body);
}

void LastRecv::setHeader(const std::weak_ptr<Header>& header){
    header_ = header;
}

void LastRecv::setHeadBody(const std::vector<unsigned char> &bytes){
    head_body_ = Decode::toHexUpperString(bytes);
}

Version& LastRecv::getVersion() {
    return *version_;
}

Header& LastRecv::getHeader() {
    return *header_.lock();
}

std::string LastRecv::getHeadBody() {
    return head_body_;
}

bool LastRecv::hasHeader(){
    if(header_.lock() == nullptr){
        return false;
    }
    return true;
}