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

#include "../Socket/ClientConnection.h"
#include "../Application/Application.h"
#include "../utils.h"

#define DEFAULT_PORT 12000
#define DEFAULT_POOL_SIZE 4

typedef boost::shared_ptr<ClientConnection> client_ptr;

class Server {
    boost::asio::io_service _service;
    boost::thread_group thread_group;
    int poolSize; //Strongly recommended init by count of kernels
    int port;

    void handleClient();
    void startAccept();

    boost::mutex mx_;
    std::vector<client_ptr> clients;
public:
    Server():
               port(DEFAULT_PORT),
               poolSize(DEFAULT_POOL_SIZE)
            {
                std::cout<<"Server()"<<std::endl;
            }

    ~Server(){
        std::cout<<"~Server()"<<std::endl;
    }

    void start();
};


#endif //TECELASQL_SERVER_H