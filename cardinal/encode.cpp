//
// Encode.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "encode.h"

std::vector<unsigned char> Encode::to1ByteHex(uint8_t n){
    return toByteHex(n , 1);
}

std::vector<unsigned char> Encode::to2ByteHex(uint16_t n){
    return toByteHex(n , 2);
}

std::vector<unsigned char> Encode::to4ByteHex(uint32_t n){
    return toByteHex(n , 4);
}

std::vector<unsigned char> Encode::to8ByteHex(uint64_t n){
    return toByteHex(n , 8);
}

std::vector<unsigned char> Encode::toByteHex(uint64_t n, size_t length){
    std::vector<unsigned char> v(0);
    for(int i = 0 ; i < length ; i++){
        v.push_back(n >> i * 8);
    }
    return v;
}

unsigned char Encode::toByteHex(bool b) {
    std::vector<unsigned char> v(0);
    if(b){
        return 0x01;
    }
    return 0x00;
}

std::vector<unsigned char> Encode::to2ByteHexBig(uint16_t n){
    return toByteHexBig(n , 2);
}

std::vector<unsigned char> Encode::toByteHexBig(uint64_t n, size_t length){
    std::vector<unsigned char> v(0);
    for(int i = (length-1) ; i >= 0 ; i--){
        v.push_back(n >> i * 8);
    }
    return v;
}


std::vector<unsigned char> Encode::fill(const std::string &str) {
    return fill(str, 0);
}


std::vector<unsigned char> Encode::fill(const std::string &str, size_t length){
    const char* str_ptr = str.c_str();
    std::vector<unsigned char> lead;
    size_t cp = 0;
    for( ; cp < str.size() ; cp++){
        lead.push_back(*str_ptr);
        str_ptr++;
    }

    for( ; cp < length ; cp++){
        lead.push_back(0x00);
    }
    return lead;
}

std::vector<unsigned char> Encode::toBytesFromHexStr(const std::string &hex_bin) {
    std::vector<unsigned char> bytes;
    for (unsigned int i = 0; i < hex_bin.length(); i += 2) {
        std::string byteString = hex_bin.substr(i, 2);
        char byte = (char) strtol(byteString.c_str(), nullptr, 16);
        bytes.push_back(byte);
    }
    return bytes;
}