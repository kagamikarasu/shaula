//
// VarStr.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/

#include "var_str.h"

VarStr::VarStr(const std::vector<unsigned char> &bytes) : var_int_(bytes) {
    body_ = {&bytes[var_int_.getPosition()], &bytes[var_int_.getPayloadLength()]};
}

VarStr::VarStr(const std::string &str) : var_int_(str) {
    body_ = {str.begin(), str.end()};
}

std::vector<unsigned char> VarStr::getBody(){
    return body_;
}

std::string VarStr::getBodyString(){
    return std::string(body_.begin(), body_.end());
}

uint64_t VarStr::getBodyLength() {
    return var_int_.getBodyLength();
}

uint64_t VarStr::getPayloadLength() {
    return var_int_.getPayloadLength();
}

std::vector<unsigned char> VarStr::getPayload(){
    std::vector<unsigned char> result;

    result.push_back(var_int_.getBodyLength());
    result.insert(result.end(), body_.begin(), body_.end());

    return result;
}