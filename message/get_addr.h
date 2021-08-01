//
// GetAddr.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_GET_ADDR_H
#define SHAULA_GET_ADDR_H

#include "message.h"

/**
 * Create a GetAddr request.
 * GetAddr is an empty payload.
 */
class GetAddr : public Message {
public:
    explicit GetAddr();
};


#endif //SHAULA_GET_ADDR_H
