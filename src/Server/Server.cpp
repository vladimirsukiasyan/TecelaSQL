//
// Created by vladimir on 07.04.19.
//

#include "Server.h"

void Server::startAccept() {
    boost::asio::ip::tcp::acceptor acceptor(
            _service,
            boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port));
    acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));

    while (true) {
        client_ptr client_connection(new ClientConnection(_service));
        acceptor.accept(client_connection->sock());
        boost::recursive_mutex::scoped_lock lock (mx_);
        clients.push_back(client_connection);
    }
}


void Server::start() {
    //парсим конфиг файл

    std::cerr << "listen on port: " << port << std::endl;
    thread_group.create_thread(boost::bind(
                    &Server::startAccept,
                    this)
    );

    for (int i = 0; i < poolSize; ++i)
        thread_group.create_thread(boost::bind(
                        &Server::handleClient,
                        this)
        );

    thread_group.join_all();
}

void Server::handleClient() {
    while (true) {
        boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
        boost::lock_guard<boost::mutex> lock(mx_);
        for (auto client = clients.begin(); client != clients.end(); ++client)
            (*client)->client_session();
        // erase clients that timed out
//        clients.erase(std::remove_if(clients.begin(), clients.end(),
//                                     boost::bind(&talk_to_client::timed_out,_1)), clients.end());
    }

}

