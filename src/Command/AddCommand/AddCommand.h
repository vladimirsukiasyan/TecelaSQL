#include <utility>

#ifndef TECELASQL_ADDCOMMAND_H
#define TECELASQL_ADDCOMMAND_H

#include <iostream>
#include <mutex>

#include "../Command.h"
#include "../../Socket/Socket.h"
#include "../../utils.h"
#include "../../exceptions.h"

class AddCommand : public Command {
public:
    //инициализация команды
    AddCommand(std::string key,
               long long exptime,
               long long length,
               Socket::ptr &client_socket
    ) :
            key(std::move(key)),
            exptime(exptime),
            length(length),
            value(nullptr),
            client_socket(Socket::ptr(client_socket))
    {}

    ~AddCommand() {
        delete value;
    }

    void execute() override;

    void setValue(std::byte *value);

    std::string toStr();

private:
    const std::string key;
    long long exptime;
    long long length;
    std::byte *value;
    Socket::ptr client_socket;
    std::recursive_mutex _mx;
};


#endif //TECELASQL_ADDCOMMAND_H