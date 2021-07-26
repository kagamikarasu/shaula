//
// Version.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_VERSION_H
#define SHAULA_VERSION_H

#include "Message.h"

struct {
    uint8_t version = 4;
    uint8_t service = 8;
    uint8_t timestamp = 8;
    uint8_t addr_recv = 26;
    uint8_t addr_from = 26;
    uint8_t nonce = 8;
    uint8_t start_height = 4;
    uint8_t relay = 1;
} VersionSize;

class Version : public Message {
    uint32_t version_{};
    uint64_t service_{};
    uint64_t timestamp_{};
    NetAddr addr_recv_;
    NetAddr addr_from_;
    std::vector<unsigned char> nonce_;
    std::string user_agent_;
    uint32_t start_height_{};
    bool relay_{};
public:
    explicit Version(Endpoint endpoint){
        setVersion(versionMeta.PROTOCOL_VERSION_NUMBER);
        setService(versionMeta.SERVICE);
        setTimestamp();
        setAddrRecv(endpoint);
        setAddrFrom(endpoint);
        setNonce(Crypt::getRand(8));
        setUserAgent(versionMeta.USER_AGENT);
        setBlockStart(0);
        setRelay(true);

        setCommand(Command.VERSION);
    }

    Version()= default;

    /**
     *
     * @return
     */
    std::vector<unsigned char> getMessage() override;

    /**
     *
     */
    void setVersion(uint32_t);

    /**
     *
     */
    void setService(uint64_t);

    /**
     *
     */
    void setTimestamp();

    /**
     *
     */
    void setAddrRecv(Endpoint&);

    /**
     *
     */
    void setAddrFrom(Endpoint&);

    /**
     *
     */
    void setNonce(std::vector<unsigned char>);

    /**
     *
     */
    void setUserAgent(std::string);

    /**
     *
     */
    void setBlockStart(uint32_t);

    /**
     *
     */
    void setRelay(bool);

    /**
     *
     */
    void setPayload();
};


#endif //SHAULA_VERSION_H
