//
// Display.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//

#include "display.h"
#include <ncurses.h>

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

    addstr("Client Connection.\n");
    _clientHeader();
    _clientConnectionList();

    addstr("\n");

    /*
    addstr("Server Connection List.\n");
    _serverHeader();
    _serverConnectionList();
    */

    timeout(500);
    char ctr = getch();
    if (0 <= ctr && ctr < 32){
        timeout(-1);
        char input_str[16];
        getstr(input_str);
    }
    _show();
}

void Display::_clientHeader(){
    addstr("Thread\t\t");
    addstr("Address\t\t\t");
    addstr("UserAgent\t\t");
    addstr("Block\t\t");
    addstr("RecvHeader\t");
    addstr("RecvHeadBody\n");
}

void Display::_clientConnectionList(){
    std::map<std::string, Client> c = std::map(ClientPool::getConnectionList());
    for(auto v : c){
        addstr(_getFillString(v.second.getRunThreadId(), 16).c_str());
        addstr(_getFillString(v.first, 24).c_str());

        if(!v.second.getLastReceiveBodyHead().empty()) {
            addstr(_getFillString(v.second.getVersion()->getUserAgent(), 24).c_str());
            addstr(_getFillString(v.second.getVersion()->getBlockHeight(), 16).c_str());
            addstr(_getFillString(v.second.getLastReceiveHeader()->getCommand(), 16).c_str());
            addstr(v.second.getLastReceiveBodyHead().c_str());
        }
        addstr("\n");
    }
}

void Display::_serverHeader(){
    addstr("Thread\t\t");
    addstr("Address\n");
}

void Display::_serverConnectionList(){
    std::vector<Session> s = Server::getConnectionList();
    for(auto v : s){
        addstr(_getFillString(v.getRunThreadId(), 16).c_str());
        addstr(_getFillString(v.getAddress(), 24).c_str());
        addstr("\n");
    }
}

std::string Display::_getFillString(const std::string &str, uint8_t max_size){
    // Make copy
    std::string result = std::string(str);
    for(size_t i = str.size() ; i < max_size ; ++i) {
        result += " ";
    }

    if(str.size() >= max_size){
        result.erase(max_size);
    }
    return result;
}

std::string Display::_mask(const std::string &str, uint8_t sp){
    // Make copy
    std::string result = std::string(str);

    result.erase(sp);

    for(size_t i = 0 ; i < str.size() - sp ; ++i){
        result += "*";
    }
    return result;
}

void Display::_clear(){
    refresh();
    clear();
}