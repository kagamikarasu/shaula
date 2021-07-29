//
// Display.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include <client/ClientPool.h>
#include "Display.h"

Display::Display(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts){
    std::shared_ptr<boost::asio::io_context> context_show = std::make_shared<boost::asio::io_context>();
    context_show->post(_init);
    io_contexts.push_back(context_show);
}

Display* Display::getInstance(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts){
    static Display display(io_contexts);
    return &display;
}

void Display::show(std::vector<std::shared_ptr<boost::asio::io_context>> &io_contexts){
    getInstance(io_contexts);
}

void Display::_init(){
    initscr();
    _show();
}

void Display::_show(){
    _clear();
    _header();
    _clientConnectionList();

    usleep(500000);
    _show();
}

void Display::_header(){
    addstr("Address\n");
}

void Display::_clientConnectionList(){
    std::map<std::string, Client> c = ClientPool::getConnectionList();
    for(auto v : c){
        addstr(v.first.c_str());
        addstr(" - ");
        addstr(v.second.getVersion()->getUserAgent().c_str());
        addstr(" - ");
        addstr(v.second.getLastReceiveHeader()->getCommand().c_str());
        addstr("\n");
    }
}

void Display::_clear(){
    refresh();
    clear();
}