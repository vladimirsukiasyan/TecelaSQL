//
// Created by vladimir on 13.04.19.
//

#ifndef TECELASQL_APPLICATION_H
#define TECELASQL_APPLICATION_H


#include <iostream>
#include <boost/function.hpp>

#include "../Socket/Socket.h"
#include "../Command/Command.h"
#include "../Query/Query.h"

class Application {

    Query *_query;
    Command *_command;
    Socket::ptr _client_socket;

    void handle_headline(const boost::system::error_code &, size_t);

    void handle_valueline(const boost::system::error_code &, size_t);

    void handle_response(const boost::system::error_code &, size_t);

    Socket::callback_function getCallbackFunction(void(Application::*pFunction)(const boost::system::error_code &error, size_t bytes_transferred));

public:

    explicit Application(const Socket::ptr &socket):
            _query(new Query(socket)),
            _command(nullptr),
            _client_socket(Socket::ptr(socket))
    {
        auto responseCallbackFunc=getCallbackFunction(&Application::handle_response);
        _client_socket->setResponseCallbackFunc(responseCallbackFunc);
    }

    ~Application() {
        delete _query;
        delete _command;
    }

    void handle_client();
};


#endif //TECELASQL_APPLICATION_H
