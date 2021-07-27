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

/**
 * Version class
 * See https://en.bitcoin.it/wiki/Protocol_documentation#version
 * After the connection is established, the Version and Verack can be received by sending the Version command.
 */
class Version : public Message {
    /**
     * Version Number
     */
    uint32_t version_{};

    /**
     * Service
     * See https://en.bitcoin.it/wiki/Protocol_documentation#version
     */
    uint64_t service_{};

    /**
     * Timestamp
     */
    uint64_t timestamp_{};

    /**
     * NetAddr Recv
     */
    NetAddr addr_recv_;

    /**
     * NetAddr Emmit
     */
    NetAddr addr_from_;

    /**
     * random value
     */
    std::vector<unsigned char> nonce_;

    /**
     * User Agent
     */
    std::string user_agent_;

    /**
     * The height of the block you are holding
     */
    uint32_t start_height_{};

    /**
     * Whether the remote peer should announce relayed transactions or not,
     * See https://github.com/bitcoin/bips/blob/master/bip-0037.mediawiki
     */
    bool relay_{};

public:
    /**
     * Create a constructor for request creation.
     * The IP/Port is stored in the argument Endpoint, and NetAddr is created using this.
     * @param endpoint
     */
    explicit Version(const Endpoint &endpoint);

    /**
     * Override getMessage of the message class to get a message that can be sent.
     * @return
     */
    std::vector<unsigned char> getMessage() override;

private:
    /**
     * Set Version Number From Int
     */
    void setVersion(uint32_t);

    /**
     * Set Service From Int
     */
    void setService(uint64_t);

    /**
     * Set Now
     */
    void setTimestamp();

    /**
     * Set NetAddr Recv
     */
    void setAddrRecv(const Endpoint &endpoint);

    /**
     * Set NetAddr Emmit
     */
    void setAddrFrom(const Endpoint &endpoint);

    /**
     * Set Nonce
     */
    void setNonce(std::vector<unsigned char>);

    /**
     * Set User agent
     */
    void setUserAgent(std::string);

    /**
     * Set BlockStart
     */
    void setBlockStart(uint32_t);

    /**
     * Set Relay
     */
    void setRelay(bool);

    /**
     * Set Payload
     */
    void setPayload();
};


#endif //SHAULA_VERSION_H
