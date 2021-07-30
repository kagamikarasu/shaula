//
// Display.h
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#ifndef SHAULA_DISPLAY_H
#define SHAULA_DISPLAY_H

#include <vector>
#include <memory>
#include <boost/asio/io_context.hpp>
#include <ncurses.h>

/**
 * Display class
 * Running it in a separate thread.
 */
class Display {

    /**
     * Singleton
     * @param io_contexts
     */
    explicit Display(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts);

    /**
     * Get Instance
     * @param io_contexts
     * @return
     */
    static Display* getInstance(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts);

    /**
     * Initialization of ncurses
     */
    static void _init();

    /**
     * Loop display
     */
    static void _show();

    /**
     * Clearing the console
     */
    static void _clear();

    /**
     * Display the header
     */
    static void _header();

    /**
     * Display the connected list
     */
    static void _clientConnectionList();

    static std::string _getFillString(const std::string &str, uint8_t max_size);
public:
    /**
     * drawing function
     * @param io_contexts
     */
    static void show(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts);

    static std::string _mask(const std::string &str, uint8_t sp);
};


#endif //SHAULA_DISPLAY_H
