//
// Define.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_DEFINE_H
#define SHAULA_DEFINE_H


struct {
    uint8_t NODE_NETWORK = 1;
    uint8_t NODE_GETUTXO = 2;
    uint8_t NODE_BLOOM = 4;
    uint8_t NODE_WITNESS = 8;
    uint8_t NODE_XTHIN = 16;
    uint8_t NODE_COMPACT_FILTERS = 64;
    uint16_t NODE_NETWORK_LIMITED = 1024;
} serviceDef;

struct {
    uint16_t SERVICE = serviceDef.NODE_NETWORK | serviceDef.NODE_WITNESS | serviceDef.NODE_NETWORK_LIMITED;
} versionMeta;

struct {
    std::string VERSION = std::string("version");
    std::string VERACK = std::string("verack");
    std::string GETADDR = std::string("getaddr");
    std::string ADDR = std::string("addr");
    std::string PING = std::string("ping");
    std::string PONG = std::string("pong");
    std::string MEMPOOL = std::string("mempool");
} Command;

#endif //SHAULA_DEFINE_H
