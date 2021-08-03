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
    const uint8_t NODE_NETWORK = 1;
    const uint8_t NODE_GETUTXO = 2;
    const uint8_t NODE_BLOOM = 4;
    const uint8_t NODE_WITNESS = 8;
    const uint8_t NODE_XTHIN = 16;
    const uint8_t NODE_COMPACT_FILTERS = 64;
    const uint16_t NODE_NETWORK_LIMITED = 1024;
} ServiceDef;

struct {
    const char* VERSION = "version";
    const char* VERACK = "verack";
    const char* GETADDR = "getaddr";
    const char* ADDR = "addr";
    const char* PING = "ping";
    const char* PONG = "pong";
    const char* MEMPOOL = "mempool";
} CommandDef;

struct {
    const char* USER_AGENT = "/Shaula:0.0.0/";
    const uint32_t PROTOCOL_VERSION_NUMBER = 70016;
    const uint32_t SERVICE = ServiceDef.NODE_GETUTXO;
} NodeInfo;

#endif //SHAULA_DEFINE_H
