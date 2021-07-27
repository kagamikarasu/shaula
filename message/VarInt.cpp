//
// VarInt.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "VarInt.h"

VarInt::VarInt(const std::vector<unsigned char> &bytes) {
    setKey(bytes);
    setLength(bytes);
}

void VarInt::setKey(const std::vector<unsigned char> &bytes){
    if(bytes[0] == 0xFD || bytes[0] == 0xFE || bytes[0] == 0xFF){
        key_ = bytes[0];
        return;
    }
    key_ = 0x00;
}

void VarInt::setPosition(uint8_t position) {
    position_ = position;
}

void VarInt::setLength(const std::vector<unsigned char> &bytes){
    if(bytes[0] == 0xFD){
        length_ = Decode::toByteInt({&bytes[1] , &bytes[3]});
        setPosition(3);
        return;
    }

    if(bytes[0] == 0xFE){
        length_ = Decode::toByteInt({bytes[1] , bytes[5]});
        setPosition(5);
        return;
    }

    if(bytes[0] == 0xFF){
        length_ = Decode::toByteInt({bytes[1] , bytes[7]});
        setPosition(7);
        return;
    }

    length_ = Decode::toByteInt(std::vector<unsigned char>({bytes[0]}));
    setPosition(1);
}

uint64_t VarInt::getLength() {
    return length_;
}

uint8_t VarInt::getPosition() {
    return position_;
}
