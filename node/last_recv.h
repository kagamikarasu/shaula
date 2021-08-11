//
// last_recv.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_LAST_RECV_H
#define SHAULA_LAST_RECV_H

#include <message/version.h>

/**
 * Class to manage the last received data.
 */
class LastRecv{
private:
    /**
     * LastRecv Header
     */
    std::weak_ptr<Header> header_;

    /**
     * LastRecv Head Body
     */
    std::string head_body_;

    /**
     * LastRecv Version Message
     */
    std::unique_ptr<Version> version_;
public:
    LastRecv() = default;

    /**
     * Set Version
     * @param body
     */
    void setVersion(const std::vector<unsigned char> &body);

    /**
     * Set Header
     * @param header
     */
    void setHeader(const std::weak_ptr<Header> &header);

    /**
     * Set HeadBody(to HEX String)
     * @param bytes
     */
    void setHeadBody(const std::vector<unsigned char> &bytes);

    /**
     * Get LastRecv Version
     * @return
     */
    Version& getVersion();

    /**
     * Get LastRecv Header
     * @return
     */
    Header& getHeader();

    /**
     * Get LastRecv HeadBody
     * @return
     */
    std::string getHeadBody();

    /**
     * Check if you have a header.
     * @return
     */
    bool hasHeader();

};

#endif //SHAULA_LAST_RECV_H
