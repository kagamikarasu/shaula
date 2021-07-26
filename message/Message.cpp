//
// Message.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "Message.h"

void Message::setCommand(std::string &command) {
    header_->setCommand(command);
}

void Message::setPayload(std::vector<unsigned char> bytes) {
    payload_ = std::move(bytes);
}

void Message::setLength(){
    uint32_t size = payload_.size();
    header_->setPayloadLength(size);
}

void Message::setChecksum(){
    std::vector<unsigned char> sha256d = Crypt::sha256d(payload_);
    std::vector<unsigned char> checksum(0);
    for(int i = 0 ; i < HeaderSize.payload_checksum ; i++){
        checksum.push_back(sha256d[i]);
    }
    header_->setPayloadChecksum(checksum);
}

std::vector<unsigned char> Message::getMessage() {
    std::vector<unsigned char> message;
    // Payload Calc
    setLength();
    setChecksum();

    // Header
    auto header = header_->getHex();
    message.insert(message.end(), header.begin(), header.end());

    // Payload
    message.insert(message.end(), payload_.begin(), payload_.end());

    return message;
}

std::vector<unsigned char> Message::getHeader(){
    return header_->getHex();
}

std::vector<unsigned char> Message::getBody(){
    return payload_;
}

std::string Message::getCommand() {
    return header_->getCommand();
}