//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_SOCKETHANDLER_H
#define TECELASQL_SOCKETHANDLER_H


#include <boost/asio/detail/shared_ptr.hpp>
#include "../Socket/Socket.h"

class SocketHandler {

public:
    //Вызывается, когда клиент отправляет по открытому
    //сокету запрос
    virtual void socketListener(std::shared_ptr<Socket> client);


private:
    //
    virtual void parseRequest();

};


#endif //TECELASQL_SOCKETHANDLER_H
