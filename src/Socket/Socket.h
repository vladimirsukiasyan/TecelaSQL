//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_SOCKET_H
#define TECELASQL_SOCKET_H

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <string>

class Socket : public std::enable_shared_from_this<Socket> {
public:
    typedef boost::function<void(const boost::system::error_code &, size_t)> callback_function;

    typedef std::shared_ptr<Socket> ptr;

    explicit Socket(boost::asio::io_service &io);

    ~Socket();

    boost::asio::ip::tcp::socket &sock();

    void async_recv(callback_function &callback_func);

    void async_send(const std::string &response);

    void setResponseCallbackFunc(callback_function &callback_func);

    char _readBuf[1024];

private:
    boost::asio::ip::tcp::socket _sock;

    callback_function _responseCallback;

};

#endif //TECELASQL_SOCKET_H
