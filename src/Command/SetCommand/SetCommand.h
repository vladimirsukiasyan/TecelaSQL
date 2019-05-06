//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_SETCOMMAND_H
#define TECELASQL_SETCOMMAND_H

#include "../Command.h"
#include "../../Socket/Socket.h"
#include <mutex>

typedef std::shared_ptr<Socket> socket_ptr;

class SetCommand : public Command {
    //инициализация команды
    SetCommand(std::string &key,
               long long exptime,
               long long length,
               socket_ptr client_socket
    ) :
            key(key),
            exptime(exptime),
            length(length),
            value(nullptr),
            client_socket(client_socket) {
        std::cout << "SetCommand" << std::endl;
    }

    ~SetCommand() {
        std::cout << "~SetCommand" << std::endl;
        delete value;
    }

    void execute() override;

    void setValue(std::byte *value);

private:
    const std::string key;
    long long exptime;
    long long length;
    std::byte *value;
    socket_ptr client_socket;
};

#endif //TECELASQL_SETCOMMAND_H
