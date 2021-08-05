//
// Message.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include <boost/asio/write.hpp>
#include "message.h"

Message::Message() : header_(std::make_unique<Header>()){
}

Message::Message(const Header &header, const std::vector<unsigned char> &body) {
    setHeader(header);
    setPayload(body);
}

void Message::setHeader(const Header &header) {
    header_ = std::make_unique<Header>(header);
}

void Message::setPayload(const std::vector<unsigned char> &bytes) {
    payload_ = bytes;
}

void Message::setCommand(const char* &command) {
    header_->setCommand(command);
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

    // Set Header
    auto header = header_->getHex();
    message.insert(message.end(), header.begin(), header.end());

    // Set Payload
    message.insert(message.end(), payload_.begin(), payload_.end());

    return message;
}

std::vector<unsigned char> Message::getBodyHeadBytes(){
    if(payload_.size() >= 40){
        return {&payload_[0], &payload_[40]};
    }
    return payload_;
}

void Message::sendMessage(boost::asio::ip::tcp::socket &socket, const boost::asio::yield_context &yield){
    std::unique_ptr<std::vector<unsigned char>> send_data =
            std::make_unique<std::vector<unsigned char>>(this->getMessage());
    boost::asio::async_write(socket, boost::asio::buffer(*send_data), yield);
}