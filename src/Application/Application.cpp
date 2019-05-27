//
// Created by vladimir on 13.04.19.
//
#include "Application.h"

void Application::handle_client(Socket::ptr client_socket) {

    std::thread producer([&](){
        std::lock_guard<std::mutex> lock(_mx);
        _clientQueue.push(new Client(client_socket));
    });

    std::thread consumer([&](){
        std::lock_guard<std::mutex> lock(_mx);
        if(!_clientQueue.empty()){
            auto client=_clientQueue.front();

            client->setDisconnectCallback([client](){
                //Disconnect callback
                delete client;
            });

            _clientQueue.pop();
            client->handle_request();
        }
    });

    producer.join();
    consumer.join();
}