#include <utility>

//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_DELETECOMMAND_H
#define TECELASQL_DELETECOMMAND_H

#include <mutex>

#include "../Command.h"
#include "../../Socket/Socket.h"
#include "../../utils.h"
#include "../../exceptions.h"


class DeleteCommand : public Command {
public:
    DeleteCommand(std::string key,
                  Socket::ptr &client_socket
    ) :
            key(std::move(key)),
            client_socket(Socket::ptr(client_socket)) {};

    std::string toStr();

    void execute() override;

private:
    const std::string key;
    Socket::ptr client_socket;
};


#endif //TECELASQL_DELETECOMMAND_H