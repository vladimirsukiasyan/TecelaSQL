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


class ClientConnection: public std::enable_shared_from_this<ClientConnection> {
    boost::asio::ip::tcp::socket _sock;
    enum { max_msg = 1024 };
    int _already_read;
    char _buff[max_msg];
    Application *app;

public:
    ClientConnection(boost::asio::io_service &io):
        _sock(io)
//        app(new Application())
        {};

    ~ClientConnection(){
        std::cout<<"ClientConnectionConnection()"<<std::endl;
        delete app;
    }

    boost::asio::ip::tcp::socket &sock() {
        return _sock;
    }

    void client_session();

    std::string recv();

    void send(const std::string &response);

    void closeConnection();

};


#endif //TECELASQL_SOCKET_H
