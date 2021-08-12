//
// node.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#include "node.h"

Node::Node(boost::asio::io_context &io_context) :
        io_context_(io_context),
        receive_buffer_(boost::asio::streambuf(2048000)),
        socket_(io_context),
        timeout_(io_context),
        last_recv_(){
}

std::unique_ptr<Header> Node::getHeader(const boost::asio::yield_context &yield){
    boost::asio::async_read(
            socket_, receive_buffer_,
            boost::asio::transfer_exactly(HeaderSize.length), yield);

    auto* rd = boost::asio::buffer_cast<const unsigned char*>(receive_buffer_.data());
    size_t rs = receive_buffer_.size();

    std::vector<unsigned char> h_rdv(rd, rd + rs);
    std::unique_ptr<Header> header = std::make_unique<Header>(h_rdv);

    // Consume Header Size
    receive_buffer_.consume(rs);
    return header;
}

std::vector<unsigned char> Node::getBody(const boost::asio::yield_context &yield, Header &header){
    boost::asio::async_read(socket_, receive_buffer_, boost::asio::transfer_exactly(header.getPayloadLength()), yield);
    auto* rd = boost::asio::buffer_cast<const unsigned char*>(receive_buffer_.data());
    size_t rs = receive_buffer_.size();

    std::vector<unsigned char> s_rdv(rd, rd + rs);

    // Consume Body Size
    receive_buffer_.consume(rs);

    return s_rdv;
}

void Node::setRunThreadId(){
    std::ostringstream thread_id_stream;
    thread_id_stream << boost::this_thread::get_id();
    run_thread_id_ = thread_id_stream.str();
}

std::string Node::getRunThreadId(){
    return run_thread_id_;
}

bool Node::isOpen() {
    return socket_.is_open();
}

void Node::close(){
    socket_.close();
}

LastRecv& Node::getLastRecv() {
    return last_recv_;
}

NodeStruct Node::getStruct(){
    return {io_context_, socket_, timeout_, endpoint_, last_send_, last_recv_};
}

void Node::setDefaultListener() {
    NodeStruct ns = getStruct();

    listeners_.push_back(std::make_unique<ListenerVersion>(ns));
    listeners_.push_back(std::make_unique<ListenerVerack>(ns));
    listeners_.push_back(std::make_unique<ListenerAddr>(ns));
    listeners_.push_back(std::make_unique<ListenerPing>(ns));
}

void Node::addListener(std::vector<std::unique_ptr<ListenerIF>> &listener) {
    listeners_ = std::move(listener);
}
