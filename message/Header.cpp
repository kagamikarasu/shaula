//
// Header.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "Header.h"

Header::Header(std::vector<unsigned char> header_bytes) {
    magic_ = {&header_bytes[0], &header_bytes[4]};

    std::vector<unsigned char> command = {&header_bytes[4], &header_bytes[16]};
    setCommand(command);

    std::vector<unsigned char> payload_length = {&header_bytes[16], &header_bytes[20]};
    setPayloadLength(payload_length);

    payload_checksum_ = {&header_bytes[20], &header_bytes[24]};
}

void Header::setMagic(std::vector<unsigned char> magic){
    magic_ = std::move(magic);
}

void Header::setCommand(std::string &command){
    command_ = command;
}

void Header::setCommand(std::vector<unsigned char> &command){
    command_ = Decode::unFillToString(command);
}

void Header::setPayloadLength(uint32_t &payload_length) {
    payload_length_ = payload_length;
}

void Header::setPayloadLength(std::vector<unsigned char> &payload_length){
    payload_length_ = Decode::toByteInt(payload_length);
}

void Header::setPayloadChecksum(std::vector<unsigned char> payload_checksum){
    payload_checksum_ = std::move(payload_checksum);
}

std::vector<unsigned char> Header::getMagic(){
    return magic_;
}

std::string Header::getCommand(){
    return command_;
}

uint32_t Header::getPayloadLength(){
    return payload_length_;
}

std::vector<unsigned char> Header::getPayloadChecksum(){
    return payload_checksum_;
}

bool Header::isVersion(){
    return Command.VERSION == getCommand();
}

bool Header::isVerack(){
    return Command.VERACK == getCommand();
}

bool Header::isAddr(){
    return Command.ADDR == getCommand();
}

bool Header::isGetAddr(){
    return Command.GETADDR == getCommand();
}

bool Header::isPing(){
    return Command.PING == getCommand();
}

bool Header::isPong(){
    return Command.PONG == getCommand();
}

bool Header::isMempool(){
    return Command.MEMPOOL == getCommand();
}

std::vector<unsigned char> Header::getHex(){
    std::vector<unsigned char > header;

    header.insert(header.end(), magic_.begin(), magic_.end());

    auto command = Encode::fill(command_, HeaderSize.command);
    header.insert(header.end(), command.begin(), command.end());

    auto payload_length = Encode::to4ByteHex(payload_length_);
    header.insert(header.end(), payload_length.begin(), payload_length.end());

    header.insert(header.end(), payload_checksum_.begin(), payload_checksum_.end());

    return header;
}