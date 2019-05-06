#ifndef TECELASQL_ADDCOMMAND_H
#define TECELASQL_ADDCOMMAND_H

#include <iostream>
#include "../Command.h"
#include <mutex>
#include "../../Socket/Socket.h"

typedef std::shared_ptr<Socket> socket_ptr;

class AddCommand : public Command {
public:
    //инициализация команды
    AddCommand(std::string &key,
               long long exptime,
               long long length,
               socket_ptr client_socket
    ) :
            key(key),
            exptime(exptime),
            length(length),
            value(nullptr),
            client_socket(client_socket) {
        std::cout << "AddCommand()" << std::endl;
    }

    ~AddCommand() {
        std::cout << "~AddCommand()" << std::endl;
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


#endif //TECELASQL_ADDCOMMAND_H