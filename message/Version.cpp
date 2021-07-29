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

Version::Version(const Endpoint &endpoint) {
    setVersion(versionMeta.PROTOCOL_VERSION_NUMBER);
    setService(versionMeta.SERVICE);
    setTimestamp();
    setAddrRecv(endpoint);
    setAddrFrom(endpoint);
    setNonce(Crypt::getRandNonce(8));
    setUserAgent(versionMeta.USER_AGENT);
    setBlockStart(0);
    setRelay(true);

    setCommand(Command.VERSION);
}

Version::Version(const std::vector<unsigned char> &bytes) {
    uint32_t sp = 0;
    setVersion({&bytes[sp], &bytes[sp+=4]});
    setService({&bytes[sp], &bytes[sp+=8]});
    setTimestamp({&bytes[sp], &bytes[sp+=8]});
    setAddrRecv({&bytes[sp], &bytes[sp+=26]});
    setAddrFrom({&bytes[sp], &bytes[sp+=26]});
    setNonce({&bytes[sp], &bytes[sp+=8]});
    // explicitly
    setUserAgent(std::vector<unsigned char>({&bytes[sp], &bytes[bytes.size()]}));

    // Add the payload of the UserAgent
    sp += user_agent_.getPayloadLength();

    setBlockStart(std::vector<unsigned char>({&bytes[sp], &bytes[sp+=4]}));

    // Relay is a 1-byte file, so it's the same.
    setRelay(bytes[sp]);
}

void Version::setVersion(uint32_t version){
    version_ = version;
}

void Version::setVersion(const std::vector<unsigned char> &bytes){
    setVersion(Decode::toByteInt(bytes));
}

void Version::setService(uint64_t service){
    service_ = service;
}

void Version::setService(const std::vector<unsigned char> &bytes){
    setService(Decode::toByteInt(bytes));
}

void Version::setTimestamp(){
    timestamp_ = std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
}

void Version::setTimestamp(uint64_t timestamp) {
    timestamp_ = timestamp;
}

void Version::setTimestamp(const std::vector<unsigned char> &bytes) {
    setTimestamp(Decode::toByteInt(bytes));
}

void Version::setAddrRecv(const Endpoint &endpoint) {
    addr_recv_.setAddr(endpoint);
    addr_recv_.setPort(endpoint);
    addr_recv_.setService({0x00});
}

void Version::setAddrRecv(const std::vector<unsigned char> &bytes) {
    addr_recv_ = std::move(NetAddr(bytes));
}

void Version::setAddrFrom(const Endpoint &endpoint){
    // After Zero Return
    addr_from_.setAddr(endpoint);
    addr_from_.setPort(endpoint);
    addr_from_.setService();
}

void Version::setAddrFrom(const std::vector<unsigned char> &bytes) {
    addr_from_ = std::move(NetAddr(bytes));
}

void Version::setNonce(std::vector<unsigned char> nonce){
    nonce_ = std::move(nonce);
}

void Version::setUserAgent(const std::string &user_agent){
    user_agent_ = std::move(VarStr(user_agent));
}

void Version::setUserAgent(const std::vector<unsigned char> &bytes){
    user_agent_ = std::move(VarStr(bytes));
}

void Version::setBlockStart(uint32_t start_height){
    start_height_ = start_height;
}

void Version::setBlockStart(const std::vector<unsigned char> &bytes) {
    start_height_ = Decode::toByteInt(bytes);
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

    auto user_agent = user_agent_.getPayload();
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

std::string Version::getUserAgent(){
    return user_agent_.getBodyString();
}

std::string Version::getBlockHeight(){
    return std::to_string(start_height_);
}