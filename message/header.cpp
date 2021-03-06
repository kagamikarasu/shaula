//
// Header.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "header.h"

Header::Header() {
    setMagic(Config::getNetwork());
}

Header::Header(const std::vector<unsigned char> &header_bytes) {
    setMagic(std::vector<unsigned char>({&header_bytes[0], &header_bytes[4]}));
    setCommand(std::vector<unsigned char>({&header_bytes[4], &header_bytes[16]}));
    setPayloadLength(std::vector<unsigned char>({&header_bytes[16], &header_bytes[20]}));
    setPayloadChecksum(std::vector<unsigned char>({&header_bytes[20], &header_bytes[24]}));
}

void Header::setMagic(const std::vector<unsigned char> &magic){
    magic_ = magic;
}

void Header::setCommand(const std::string &command){
    command_ = command;
}

void Header::setCommand(const std::vector<unsigned char> &command){
    command_ = Decode::unFillToString(command);
}

void Header::setPayloadLength(uint32_t &payload_length) {
    payload_length_ = payload_length;
}

void Header::setPayloadLength(const std::vector<unsigned char> &payload_length){
    payload_length_ = Decode::toByteInt(payload_length);
}

void Header::setPayloadChecksum(const std::vector<unsigned char> &payload_checksum){
    payload_checksum_ = payload_checksum;
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
    return CommandDef.VERSION == getCommand();
}

bool Header::isVerack(){
    return CommandDef.VERACK == getCommand();
}

bool Header::isAddr(){
    return CommandDef.ADDR == getCommand();
}

bool Header::isGetAddr(){
    return CommandDef.GETADDR == getCommand();
}

bool Header::isPing(){
    return CommandDef.PING == getCommand();
}

bool Header::isPong(){
    return CommandDef.PONG == getCommand();
}

bool Header::isMempool(){
    return CommandDef.MEMPOOL == getCommand();
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