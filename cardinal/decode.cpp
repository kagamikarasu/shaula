//
// Decode.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include <string>
#include <sstream>
#include <iomanip>
#include "decode.h"

int32_t Decode::toByteInt(const std::vector<unsigned char> &bytes){
    int n = 0;
    for(int i = 0 ; i < bytes.size() ; ++i){
        n += bytes[i] * std::pow(256, i);
    }
    return n;
}

int32_t Decode::toByteIntBig(const std::vector<unsigned char> &bytes){
    int n = 0;
    for(int i = 0 ; i < bytes.size() ; ++i){
        n += bytes[i] * std::pow(256, (bytes.size()-1) - i);
    }
    return n;
}

std::string Decode::unFillToString(const std::vector<unsigned char> &bytes){
    std::vector<char> v_str;
    for(char s : bytes){
        if(s == 0x00){
            continue;
        }
        v_str.push_back(s);
    }
    return std::string(v_str.begin(), v_str.end());
}

std::string Decode::toHexUpperString(const std::vector<unsigned char> &bytes){
    std::ostringstream result;
    for (auto v : bytes) {
        result << std::hex << std::setfill('0') << std::setw(2) << std::uppercase << (int)v;
    }
    return result.str();
}

std::string Decode::toHexLowerString(const std::vector<unsigned char> &bytes){
    std::ostringstream result;
    for (auto v : bytes) {
        result << std::hex << std::setfill('0') << std::setw(2) << std::nouppercase << (int)v;
    }
    return result.str();
}