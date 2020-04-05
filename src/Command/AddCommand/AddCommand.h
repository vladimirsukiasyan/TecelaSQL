#include <utility>

#ifndef TECELASQL_ADDCOMMAND_H
#define TECELASQL_ADDCOMMAND_H

#include <iostream>
#include <mutex>

#include "../Command.h"
#include "../../Socket/Socket.h"
#include "../../HashTable/HashTable.h"
#include "../../exceptions.h"

class AddCommand : public Command {
public:
    //инициализация команды
    AddCommand(std::string key,
               long long exptime,
               long long length,
               std::byte *value
    ) :
            key(std::move(key)),
            exptime(exptime),
            length(length),
            value(value)
            {}

    ~AddCommand() override {
        delete value;
    }

    std::string execute() override;

    std::string toStr();

private:
    const std::string key;
    long long exptime;
    long long length;
    std::byte *value;

    std::recursive_mutex _mx;
};


#endif //TECELASQL_ADDCOMMAND_H