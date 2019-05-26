//
// Created by vladimir on 07.04.19.
//

#include "Server.h"

HashTable *pTable;

void Server::startAccept() {

    //TODO commit as safety memory allocation with creating of shared_ptr
    Socket::ptr client=std::make_shared<Socket>(_service);
    //TODO проследить чтобы Socket удалялся, когда клиент закрывает соединение
    _acceptor.async_accept(
            client->sock(),
            boost::bind(
                    &Server::handleRequest,
                    this,
                    client,
                    boost::asio::placeholders::error
            )
    );
}

void Server::handleRequest(Socket::ptr client_socket, const boost::system::error_code &err) {
    if (err) return;
    std::cerr << "+client: " << client_socket->sock().remote_endpoint().address().to_string().c_str() << std::endl;

    startAccept();

    app->handle_client(client_socket);
}

void Server::runAsyncTaskLooping() {
    //запускаем цикл внутри каждого потока, который будет
    //ждать конца выполнения всех асинхронных задач в рамках конкретного потока
    _service.run();
}


void Server::start() {
    //парсим конфиг файл

    startAccept();

    std::cerr << "listen on _port: " << _port << std::endl;

    work_ptr dummy_work(new boost::asio::io_service::work(_service));
    for (int i = 0; i < _poolSize; ++i)
        _thread_group.add_thread(
                new boost::thread(std::bind(&Server::runAsyncTaskLooping, this)));

    _thread_group.join_all();

}

Server::Server() : _acceptor(_service),
                   _port(DEFAULT_PORT),
                   _poolSize(DEFAULT_POOL_SIZE),
                   app(new Application()){

    std::cout << "Server()" << std::endl;

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), _port);
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen(1024);
}

Server::~Server() {
    delete app;
}

