#include <utility>

//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_GETCOMMAND_H
#define TECELASQL_GETCOMMAND_H

#include <mutex>
#include "../Command.h"
#include "../../utils.h"
#include "../../exceptions.h"
#include "../../Socket/Socket.h"

class GetCommand : public Command {
public:
    //инициализация команды
    GetCommand(std::string key,
               const Socket::ptr &client_socket
    ) :
            key(std::move(key)),
            client_socket(Socket::ptr(client_socket)) {

    }

    void execute() override;

    std::string toStr();

private:
    const std::string key;
    Socket::ptr client_socket;

    std::recursive_mutex _mx;

};


#endif //TECELASQL_GETCOMMAND_H