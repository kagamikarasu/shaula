//
// GetAddr.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#ifndef SHAULA_GETADDR_H
#define SHAULA_GETADDR_H

#include "Message.h"

/**
 * Create a GetAddr request.
 * GetAddr is an empty payload.
 */
class GetAddr : public Message {
public:
    explicit GetAddr();
};


#endif //SHAULA_GETADDR_H
