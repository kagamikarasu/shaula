//
// Pong.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_PONG_H
#define SHAULA_PONG_H

#include <vector>
#include "Message.h"
#include "Define.h"

/**
 * Pong Class
 * This class is used for ping responses.
 */
class Pong : public Message{
    /**
     * random value.
     */
    std::vector<unsigned char> nonce_;

public:
    /**
     * Constructor
     * Set the ping response (nonce value).
     * @param bytes
     */
    explicit Pong(const std::vector<unsigned char> &bytes);

    /**
     * Override getMessage of the message class to get a message that can be sent.
     * @return
     */
    std::vector<unsigned char> getMessage() override;

private:
    /**
     * Set nonce.
     * @param bytes
     */
    void setNonce(const std::vector<unsigned char> &bytes);
};


#endif //SHAULA_PONG_H
