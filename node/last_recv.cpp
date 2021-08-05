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

void LastRecv::setHeader(const Header& header){
    header_ = std::make_unique<Header>(header);
}

void LastRecv::setHeadBody(const std::vector<unsigned char> &bytes){
    std::ostringstream body_head_stream;
    for (auto v : bytes) {
        body_head_stream << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << (int)v;
    }
    head_body_ = body_head_stream.str();
}

Version &LastRecv::getVersion() {
    return *version_;
}

Header &LastRecv::getHeader() {
    return *header_;
}

std::string LastRecv::getHeadBody() {
    return head_body_;
}


