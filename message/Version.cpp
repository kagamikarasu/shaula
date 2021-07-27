//
// Version.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "Version.h"

void Version::setVersion(uint32_t version){
    version_ = version;
}

void Version::setService(uint64_t service){
    service_ = service;
}

void Version::setTimestamp(){
    timestamp_ = std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
}

void Version::setAddrRecv(Endpoint &endpoint) {
    addr_recv_.setAddr(endpoint);
    addr_recv_.setPort(endpoint);
    addr_recv_.setService({0x00});
}

void Version::setAddrFrom(Endpoint &endpoint){
    // After Zero Return
    addr_from_.setAddr(endpoint);
    addr_from_.setPort(endpoint);
    addr_from_.setService();
}

void Version::setNonce(std::vector<unsigned char> nonce){
    nonce_ = std::move(nonce);
}

void Version::setUserAgent(std::string user_agent){
    user_agent_ = std::move(user_agent);
}

void Version::setBlockStart(uint32_t start_height){
    start_height_ = start_height;
}

void Version::setRelay(bool relay) {
    relay_ = relay;
}

void Version::setPayload() {
    std::vector<unsigned char> payload;

    auto version = Encode::to4ByteHex(version_);
    payload.insert(payload.end(), version.begin(), version.end());

    auto service = Encode::to8ByteHex(service_);
    payload.insert(payload.end(), service.begin(), service.end());

    auto timestamp = Encode::to8ByteHex(timestamp_);
    payload.insert(payload.end(), timestamp.begin(), timestamp.end());

    auto addr_recv = addr_recv_.getHexNoneTimestamp();
    payload.insert(payload.end(), addr_recv.begin(), addr_recv.end());

    auto addr_from = addr_from_.getZeroAddressHex();
    payload.insert(payload.end(), addr_from.begin(), addr_from.end());

    payload.insert(payload.end(), nonce_.begin(), nonce_.end());

    auto user_agent_length = user_agent_.length();
    payload.insert(payload.end(), user_agent_length);

    auto user_agent = Encode::fill(user_agent_);
    payload.insert(payload.end(), user_agent.begin(), user_agent.end());

    auto start_height = Encode::to4ByteHex(start_height_);
    payload.insert(payload.end(), start_height.begin(), start_height.end());

    payload.insert(payload.end(), relay_);

    Message::setPayload(payload);
}

std::vector<unsigned char> Version::getMessage(){
    setPayload();
    // Merge Parent Message
    return Message::getMessage();
}