//
// Created by vladimir on 13.04.19.
//

#ifndef TECELASQL_APPLICATION_H
#define TECELASQL_APPLICATION_H


#include <iostream>
#include "../utils.h"
#include "../Command/Command.h"
#include "../Query/Query.h"
#include "../Socket/Socket.h"

class Application {

    //TODO можно enum of state(CommandLineReceived,DataLineReceived) сделать
    Query *query;
    Command *command;

public:

    Application():
        query(new Query()),
        command(nullptr)
        {
            std::cout<<"Application()"<<std::endl;

        }

    ~Application(){
        std::cout<<"~Application()"<<std::endl;

        delete query;
        delete command;
    }
    void requestHandler(Socket::ptr client_socket);
};


#endif //TECELASQL_APPLICATION_H
