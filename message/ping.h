//
// Ping.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_PING_H
#define SHAULA_PING_H

#include <vector>
#include "message.h"
#include "define.h"

/**
 * Ping Class
 */
class Ping : public Message{
    /**
     * random value.
     */
    std::vector<unsigned char> nonce_;

public:
    /**
     * Constructor
     * Initialize the nonce value required for the request
     */
    explicit Ping();

    /**
     * Constructor
     * Storing the nonce value of the response.
     * @param bytes
     */
    explicit Ping(const std::vector<unsigned char> &bytes);

    /**
     * Get the nonce value
     * Assumptions used in Pong messages
     * @return
     */
    std::vector<unsigned char> getNonce();

    /**
     * Override getMessage of the message class to get a message that can be sent.
     * @return
     */
    std::vector<unsigned char> getMessage() override;

private:
    /**
     * Generate and set the nonce value.
     */
    void setNonce();

    /**
     * Set nonce.
     * @param bytes
     */
    void setNonce(const std::vector<unsigned char> &bytes);
};


#endif //SHAULA_PING_H
