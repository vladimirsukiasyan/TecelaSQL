//
// Created by vladimir on 14.04.19.
//


#ifndef TECELASQL_GETCOMMAND_H
#define TECELASQL_GETCOMMAND_H

#include "../Command.h"
#include "../../Socket/Socket.h"
#include <mutex>

typedef std::shared_ptr<Socket> socket_ptr;

class GetCommand : public Command {
public:
    //инициализация команды
    GetCommand(std::string &key,
               socket_ptr client_socket)
            : key(key),
              client_socket(client_socket) {}

    void execute() override;

private:
    const std::string key;
    socket_ptr client_socket;
};


#endif //TECELASQL_GETCOMMAND_H