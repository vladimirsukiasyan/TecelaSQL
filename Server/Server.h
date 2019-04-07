//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_SERVER_H
#define TECELASQL_SERVER_H


#include <string>
#include "../SocketHandler/SocketHandler.h"

class Server {
    std::string configuration;
    int port;
    int poolSize;

    SocketHandler socketHandler;

public:
    explicit Server(int port=8080);
    ~Server();

    void start();

};


#endif //TECELASQL_SERVER_H
