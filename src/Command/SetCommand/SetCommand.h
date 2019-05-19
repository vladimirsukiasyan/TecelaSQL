#include <utility>

//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_SETCOMMAND_H
#define TECELASQL_SETCOMMAND_H

#include <mutex>

#include "../Command.h"
#include "../../Socket/Socket.h"
#include "../../utils.h"
#include "../../exceptions.h"

class SetCommand : public Command {
public:
    //инициализация команды
    SetCommand(std::string key,
               long long exptime,
               long long length,
               Socket::ptr &client_socket
    ) :
            key(std::move(key)),
            exptime(exptime),
            length(length),
            value(nullptr),
            client_socket(Socket::ptr (client_socket))
    {}


    ~SetCommand() {
        delete value;
    }

    void execute() override;
    std::string toStr();

    void setValue(std::byte *value);

private:
    const std::string key;
    long long exptime;
    long long length;
    std::byte *value;
    Socket::ptr client_socket;

    std::recursive_mutex _mx;

};

#endif //TECELASQL_SETCOMMAND_H