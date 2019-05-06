//
// Created by vladimir on 07.04.19.
//

#include "Socket.h"

std::string Socket::recv() {
    boost::system::error_code error_code;
    _sock.read_some(boost::asio::buffer(_buf),error_code);
    if (error_code == boost::asio::error::eof)
    {
        std::cerr << "-client: " << _sock.remote_endpoint().address().to_string() << std::endl;
    }
    return _buf;
}

void Socket::send(std::string &response) {
    boost::system::error_code error_code;
    _sock.write_some(boost::asio::buffer(_sendBuf),error_code);
}


