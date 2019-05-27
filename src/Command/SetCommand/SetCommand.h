#include <utility>

//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_SETCOMMAND_H
#define TECELASQL_SETCOMMAND_H

#include <mutex>

#include "../Command.h"
#include "../../exceptions.h"
#include "../../HashTable/HashTable.h"


class SetCommand : public Command {
public:
    //инициализация команды
    SetCommand(std::string key,
               long long exptime,
               long long length,
               std::byte* value
    ) :
            key(std::move(key)),
            exptime(exptime),
            length(length),
            value(value)
    {}


    ~SetCommand() override {
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

#endif //TECELASQL_SETCOMMAND_H