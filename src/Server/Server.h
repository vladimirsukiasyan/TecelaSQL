//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_SERVER_H
#define TECELASQL_SERVER_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <iostream>

#include "../utils.h"
#include "../Socket/Socket.h"
#include "../Application/Application.h"

#define DEFAULT_PORT 12000
#define DEFAULT_POOL_SIZE 4

typedef std::shared_ptr<boost::asio::io_service::work> work_ptr;

class Server {
    boost::asio::io_service _service;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::thread_group thread_group;
    std::vector<std::shared_ptr<Application>> clients;
    int poolSize; //Strongly recommended init by count of kernels
    int port;

    void handleRequest(Socket::ptr client_socket, const boost::system::error_code &err);

    void startAccept();

    void runAsyncTaskLooping();

public:
    Server();

    ~Server() {
        std::cout << "~Server()" << std::endl;
    }

    void start();
};


#endif //TECELASQL_SERVER_H