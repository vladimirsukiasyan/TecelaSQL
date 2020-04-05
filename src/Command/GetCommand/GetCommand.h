//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_GETCOMMAND_H
#define TECELASQL_GETCOMMAND_H

#include <mutex>

#include "../Command.h"
#include "../../HashTable/HashTable.h"
#include "../../exceptions.h"

class GetCommand : public Command {
public:
    //инициализация команды
    explicit GetCommand(std::string key) :
            key(std::move(key)) {
    }

    ~GetCommand() override = default;

    std::string execute() override;

    std::string toStr();

private:
    const std::string key;

    std::recursive_mutex _mx;

};


#endif //TECELASQL_GETCOMMAND_H