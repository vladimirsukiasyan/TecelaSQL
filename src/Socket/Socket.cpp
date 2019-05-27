//
// Created by vladimir on 07.04.19.
//

#include "Socket.h"

void Socket::async_recv(callback_function &callback_func) {
    _sock.async_read_some(
            boost::asio::buffer(_readBuf),
            callback_func
    );

}
void Socket::async_send(const std::string &response) {
    std::cout << response << std::endl;

    _sock.async_write_some(
            boost::asio::buffer(response),
            _responseCallback
    );
}

boost::asio::ip::tcp::socket &Socket::sock() {
    return _sock;
}

Socket::Socket(boost::asio::io_service &io) :
        _sock(io) {}

Socket::~Socket() {}

void Socket::setResponseCallbackFunc(callback_function &callback_func) {
    _responseCallback=callback_func;
}


