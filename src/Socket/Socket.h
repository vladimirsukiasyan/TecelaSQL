//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_SOCKET_H
#define TECELASQL_SOCKET_H


#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <functional>
#include <iostream>
#include <string>

#include "../Application/Application.h"


class Socket: public std::enable_shared_from_this<Socket> {
    boost::asio::ip::tcp::socket _sock;
    char _buf[1024];
    char _sendBuf[1024];
    Application *app;

public:
    typedef std::shared_ptr<Socket> ptr;

    Socket(boost::asio::io_service &io):
        _sock(io),
        app(new Application())
        {};

    ~Socket(){
        std::cout<<"~Socket()"<<std::endl;
        delete app;
    }

    boost::asio::ip::tcp::socket &sock() {
        return _sock;
    }

    std::string recv();

    void send(std::string &response);

    void closeConnection();

};


#endif //TECELASQL_SOCKET_H
