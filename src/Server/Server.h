//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_SERVER_H
#define TECELASQL_SERVER_H

#include <string>
#include <boost/asio/io_service.hpp>
#include <boost/thread/thread_pool.hpp>
//#include "../ThreadManager/ThreadManager.h"
#include "../Application/Application.h"

#define DEFAULT_PORT 12000
#define DEFAULT_POOL_SIZE 40

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

class Server {
    std::string configuration;
    int port;
    int poolSize;
    boost::asio::io_service io_service;

    Application *app;

    void accept_handler(socket_ptr);
    void worker_thread();
public:
    explicit Server();

    ~Server();
    void start();

};


#endif //TECELASQL_SERVER_H
