//
// Created by vladimir on 07.04.19.
//

#include <boost/asio/io_service.hpp>
#include <boost/thread.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "Server.h"
#include "../Socket/Socket.h"

using namespace boost::asio;

void Server::start() {
    //парсим конфиг файл

    ip::tcp::acceptor acceptor(
            io_service,
            ip::tcp::endpoint(ip::tcp::v4(),port)
            );


    while(true){
        socket_ptr socket(new ip::tcp::socket(io_service));
        acceptor.accept(*socket);
        accept_handler(socket);
    }
}

void Server::accept_handler(socket_ptr socket) {
    app->request_handler(socket);
}

Server::Server():
    port(DEFAULT_PORT),
    poolSize(DEFAULT_POOL_SIZE),
    app(new Application())
    {}

void Server::worker_thread(){
    //запускаем цикл внутри каждого потока, который будет
    //ждать конца выполнения всех асинхронных задач в рамках конкретного потока
    io_service.run();
}
