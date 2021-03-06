//
// last_send.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#include "last_send.h"

void LastSend::setHeader(const Header& header) {
    header_ = std::make_unique<Header>(header);
}

Header &LastSend::getHeader() {
    return *header_;
}

bool LastSend::hasHeader(){
    if(header_ == nullptr){
        return false;
    }
    return true;
}

void LastSend::enableVerack() {
    isAlreadyVerack = true;
}

void LastSend::disableVerack() {
    isAlreadyVerack = false;
}

bool LastSend::isEnableVerack() {
    return isAlreadyVerack;
}
