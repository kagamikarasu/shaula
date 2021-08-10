//
// node.cpp
//
// Copyright (c) 2021 Yuya Takeda (@kagamikarasu)
//
// MIT LICENSE
// See the following LICENSE file
// https://github.com/kagamikarasu/shaula/
//
#include <node/listener/listener_if.h>
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

void Node::setAddr(){
    if(socket_.local_endpoint().address().is_v4()){
        endpoint_.local_address = boost::asio::ip::make_address_v6(
                boost::asio::ip::v4_mapped, socket_.local_endpoint().address().to_v4());
    }else{
        endpoint_.local_address = socket_.local_endpoint().address().to_v6();
    }

    if(socket_.remote_endpoint().address().is_v4()){
        endpoint_.remote_address = boost::asio::ip::make_address_v6(
                boost::asio::ip::v4_mapped, socket_.remote_endpoint().address().to_v4());
    }else{
        endpoint_.remote_address = socket_.remote_endpoint().address().to_v6();
    }

    endpoint_.local_port = socket_.local_endpoint().port();
    endpoint_.remote_port = socket_.remote_endpoint().port();
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
    return {io_context_, socket_, timeout_};
}

void Node::addListener(std::vector<std::unique_ptr<ListenerIF>> &listener) {
    listeners_ = std::move(listener);
}
