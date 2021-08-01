//
// Node.cpp
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
        receive_buffer_(std::make_shared<boost::asio::streambuf>(2048000)),
        socket_(std::make_shared<boost::asio::ip::tcp::socket>(io_context)){
}

std::unique_ptr<Header> Node::getHeader(const boost::asio::yield_context &yield){
    boost::asio::async_read(
            *socket_, *receive_buffer_,
            boost::asio::transfer_exactly(HeaderSize.length), yield);

    auto* rd = boost::asio::buffer_cast<const unsigned char*>(receive_buffer_->data());
    size_t rs = receive_buffer_->size();

    std::vector<unsigned char> h_rdv(rd, rd + rs);
    std::unique_ptr<Header> header = std::make_unique<Header>(h_rdv);

    // Consume Header Size
    receive_buffer_->consume(rs);
    return header;
}

std::vector<unsigned char> Node::getBody(const boost::asio::yield_context &yield, Header &header){
    boost::asio::async_read(*socket_, *receive_buffer_, boost::asio::transfer_exactly(header.getPayloadLength()), yield);
    auto* rd = boost::asio::buffer_cast<const unsigned char*>(receive_buffer_->data());
    size_t rs = receive_buffer_->size();

    std::vector<unsigned char> s_rdv(rd, rd + rs);

    // Consume Body Size
    receive_buffer_->consume(rs);

    return s_rdv;
}

void Node::sendVersion(const boost::asio::yield_context &yield) {
    std::unique_ptr<Version> ver = std::make_unique<Version>(endpoint_);
    std::unique_ptr<std::vector<unsigned char>> send_data = std::make_unique<std::vector<unsigned char>>(
            ver->getMessage());
    boost::asio::async_write(*socket_, boost::asio::buffer(*send_data), yield);
}

void Node::sendVerack(const boost::asio::yield_context &yield){
    std::unique_ptr<Verack> ver = std::make_unique<Verack>();
    std::unique_ptr<std::vector<unsigned char>> send_data = std::make_unique<std::vector<unsigned char>>(
            ver->getMessage());
    boost::asio::async_write(*socket_, boost::asio::buffer(*send_data), yield);
}

void Node::sendPing(const boost::asio::yield_context &yield){
    std::unique_ptr<Ping> ping = std::make_unique<Ping>();
    std::unique_ptr<std::vector<unsigned char>> send_data = std::make_unique<std::vector<unsigned char>>(
            ping->getMessage());
    boost::asio::async_write(*socket_, boost::asio::buffer(*send_data), yield);
}

void Node::sendPong(const boost::asio::yield_context &yield, const std::vector<unsigned char> &nonce){
    std::unique_ptr<Pong> pong = std::make_unique<Pong>(nonce);
    std::unique_ptr<std::vector<unsigned char>> send_data = std::make_unique<std::vector<unsigned char>>(
            pong->getMessage());
    boost::asio::async_write(*socket_, boost::asio::buffer(*send_data), yield);
}

void Node::sendGetAddr(const boost::asio::yield_context &yield){
    std::unique_ptr<GetAddr> ver = std::make_unique<GetAddr>();
    std::unique_ptr<std::vector<unsigned char>> send_data = std::make_unique<std::vector<unsigned char>>(
            ver->getMessage());
    boost::asio::async_write(*socket_, boost::asio::buffer(*send_data), yield);
}

void Node::sendMempool(const boost::asio::yield_context &yield){
    std::unique_ptr<Mempool> mempool = std::make_unique<Mempool>();
    std::unique_ptr<std::vector<unsigned char>> send_data = std::make_unique<std::vector<unsigned char>>(
            mempool->getMessage());
    boost::asio::async_write(*socket_, boost::asio::buffer(*send_data), yield);
}

void Node::sendRaw(const boost::asio::yield_context &yield, const std::string &hex_str){
    std::unique_ptr<std::vector<unsigned char>> send_data = std::make_unique<std::vector<unsigned char>>(
            Crypt::toHexFromHexStr(hex_str));
    boost::asio::async_write(*socket_, boost::asio::buffer(*send_data), yield);
}

void Node::setAddr(){
    if(socket_->local_endpoint().address().is_v4()){
        endpoint_.local_address = boost::asio::ip::make_address_v6(
                boost::asio::ip::v4_mapped, socket_->local_endpoint().address().to_v4());
    }else{
        endpoint_.local_address = socket_->local_endpoint().address().to_v6();
    }

    if(socket_->remote_endpoint().address().is_v4()){
        endpoint_.remote_address = boost::asio::ip::make_address_v6(
                boost::asio::ip::v4_mapped, socket_->remote_endpoint().address().to_v4());
    }else{
        endpoint_.remote_address = socket_->remote_endpoint().address().to_v6();
    }

    endpoint_.local_port = socket_->local_endpoint().port();
    endpoint_.remote_port = socket_->remote_endpoint().port();
}