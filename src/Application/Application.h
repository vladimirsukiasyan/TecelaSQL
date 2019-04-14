//
// Created by vladimir on 13.04.19.
//

#ifndef TECELASQL_APPLICATION_H
#define TECELASQL_APPLICATION_H


#include <boost/asio/detail/shared_ptr.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "../Command/Command.h"
#include "../Socket/Socket.h"
#include "../Query/Query.h"

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;

class Application {
    Command *command;
    Query *query;

public:
    void request_handler(socket_ptr sock);
};


#endif //TECELASQL_APPLICATION_H
