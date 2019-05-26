//
// Created by vladimir on 13.04.19.
//

#ifndef TECELASQL_APPLICATION_H
#define TECELASQL_APPLICATION_H


#include <iostream>
#include <queue>
#include <thread>
#include <mutex>

#include "../Socket/Socket.h"
#include "../Client/Client.h"

class Application {

    std::queue<Client*> _clientQueue;
    std::mutex _mx;

public:

    Application()= default;

    ~Application() = default;

    void handle_client(Socket::ptr client_socket);
};


#endif //TECELASQL_APPLICATION_H
