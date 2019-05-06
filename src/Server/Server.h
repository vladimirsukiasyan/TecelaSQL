//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_SERVER_H
#define TECELASQL_SERVER_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <functional>
#include <iostream>

#include <boost/bind.hpp>

#include "../Socket/Socket.h"
#include "../Application/Application.h"
#include "../utils.h"

#define DEFAULT_PORT 12000
#define DEFAULT_POOL_SIZE 4

typedef std::shared_ptr<boost::asio::io_service::work> work_ptr;

class Server {
    boost::asio::io_service _service;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::thread_group thread_group;
    int poolSize; //Strongly recommended init by count of kernels
    int port;
    Application *app;

    void handleRequest(Socket::ptr client_socket, const boost::system::error_code &err);

    void startAccept();

    void runAsyncTaskLooping();

public:
    Server() : _acceptor(_service),
               app(new Application()),
               port(DEFAULT_PORT),
               poolSize(DEFAULT_POOL_SIZE) {
        std::cout << "Server()" << std::endl;
    }

    ~Server() {
        delete app;
        std::cout << "~Server()" << std::endl;
    }

    void start();
};


#endif //TECELASQL_SERVER_H