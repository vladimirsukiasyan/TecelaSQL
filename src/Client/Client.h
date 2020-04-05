//
// Created by vladimir on 26.05.19.
//

#ifndef TECELASQL_CLIENT_H
#define TECELASQL_CLIENT_H


#include "../Query/Query.h"
#include "../Command/Command.h"

class Client {
    Query *_query;
    Command *_command;
    Socket::ptr _client_socket;
    std::function <void()> disconnectCallback;

    void handle_headline(const boost::system::error_code &, size_t);

    void handle_valueline(const boost::system::error_code &, size_t);

    void handle_response(const boost::system::error_code &, size_t);

    Socket::callback_function getCallbackFunction(
            void(Client::*pFunction)(const boost::system::error_code &error, size_t bytes_transferred));

public:

    explicit Client(const Socket::ptr socket) :
            _query(new Query()),
            _command(nullptr),
            _client_socket(socket)
    {
        auto responseCallbackFunc = getCallbackFunction(&Client::handle_response);
        _client_socket->setResponseCallbackFunc(responseCallbackFunc);
    }

    ~Client(){
        delete _query;
        delete _command;
    }

    void handle_request();

    void setDisconnectCallback(std::function<void()> disconnectCallback);
};


#endif //TECELASQL_CLIENT_H
