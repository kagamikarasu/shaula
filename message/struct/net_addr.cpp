//
// NetAddr.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#include "net_addr.h"
#include "config/config.h"

NetAddr::NetAddr(const std::vector<unsigned char> &bytes) {

    // For Version Message.(26bytes)
    if(bytes.size() == 26){
        setService({&bytes[0], &bytes[8]});
        setAddr({&bytes[8], &bytes[24]});
        setPort({&bytes[24], &bytes[26]});
        return;
    }

    // Other than that. Probably Addr
    setTimestamp({&bytes[0], &bytes[4]});
    setService({&bytes[4], &bytes[12]});
    setAddr({&bytes[12], &bytes[28]});
    setPort({&bytes[28], &bytes[30]});
}

void NetAddr::setTimestamp(){
    timestamp_ = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

void NetAddr::setTimestamp(const std::vector<unsigned char> &&bytes) {
    timestamp_ = Decode::toByteInt(bytes);
}

void NetAddr::setService(){
    service_ = NodeInfo.SERVICE;
}

void NetAddr::setService(const std::vector<unsigned char> &&bytes) {
    service_ = Decode::toByteInt(bytes);
}

void NetAddr::setAddr(const Endpoint &endpoint){
    if(endpoint.remote_address.is_v4()) {
        address_ = boost::asio::ip::make_address_v6(boost::asio::ip::v4_mapped, endpoint.remote_address.to_v4());
        return;
    }
    address_ = endpoint.remote_address.to_v6();
}

void NetAddr::setAddr(const std::vector<unsigned char> &&bytes) {
    std::array<unsigned char, 16> addr{};
    for(int i = 0 ; i < bytes.size() ; ++i){
        addr[i] = bytes[i];
    }
    address_ = boost::asio::ip::address_v6(addr);
}

void NetAddr::setPort(const Endpoint &endpoint){
    port_ = endpoint.remote_port;
}

void NetAddr::setPort(const std::vector<unsigned char> &bytes){
    port_ = Decode::toByteIntBig(bytes);
}

std::vector<unsigned char> NetAddr::getHex() {
    std::vector<unsigned char> result;

    auto timestamp = Encode::to4ByteHex(timestamp_);
    result.insert(result.end(), timestamp.begin(), timestamp.end());

    auto none_time = getHexNoneTimestamp();
    result.insert(result.end(), none_time.begin(), none_time.end());

    return result;
}

std::vector<unsigned char> NetAddr::getHexNoneTimestamp(){
    std::vector<unsigned char> result;

    auto service = Encode::to8ByteHex(service_);
    result.insert(result.end(), service.begin(), service.end());

    auto bytes_type = address_.to_bytes();
    result.insert(result.end(), bytes_type.begin(), bytes_type.end());

    auto port = Encode::to2ByteHexBig(port_);
    result.insert(result.end(), port.begin(), port.end());

    return result;
}

std::vector<unsigned char> NetAddr::getZeroAddressHex(){
    std::vector<unsigned char> result;

    auto service = Encode::to8ByteHex(service_);
    result.insert(result.end(), service.begin(), service.end());

    for(int i = 0 ; i < 18 ; i++){
        result.push_back(0x00);
    }
    return result;
}

std::string NetAddr::getAddressString() {
    return address_.to_string();
}

boost::asio::ip::address_v6 NetAddr::getAddressV6(){
    return address_;
}

uint16_t NetAddr::getPort(){
    return port_;
}
