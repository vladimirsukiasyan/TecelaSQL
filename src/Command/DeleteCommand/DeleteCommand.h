//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_DELETECOMMAND_H
#define TECELASQL_DELETECOMMAND_H

#include <string>
#include <mutex>
#include "../../Socket/Socket.h"
#include "../Command.h"

typedef std::shared_ptr<Socket> socket_ptr;

class DeleteCommand : public Command {
    DeleteCommand(const std::string &key,
                  socket_ptr client_socket
    ) :
            key(key),
            client_socket(client_socket) {}

    ;

    void execute() override;

private:
    const std::string key;
    socket_ptr client_socket;
};


#endif //TECELASQL_DELETECOMMAND_H
