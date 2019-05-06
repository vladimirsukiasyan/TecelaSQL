//
// Created by vladimir on 07.04.19.
//

#include "Server.h"

void Server::startAccept() {

    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen(1024);

    std::shared_ptr<Socket> client(new Socket(_service));
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

    app->requestHandler(client_socket);

    startAccept();
}

void Server::runAsyncTaskLooping() {
    //запускаем цикл внутри каждого потока, который будет
    //ждать конца выполнения всех асинхронных задач в рамках конкретного потока
    _service.run();
}

void Server::start() {
    //парсим конфиг файл

    startAccept();

    std::cerr << "listen on port: " << port << std::endl;

    work_ptr dummy_work(new boost::asio::io_service::work(_service));
    for (int i = 0; i < poolSize; ++i)
        thread_group.add_thread(
                new boost::thread(std::bind(&Server::runAsyncTaskLooping, this)));

    thread_group.join_all();

}

