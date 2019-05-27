#include <utility>

//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_DELETECOMMAND_H
#define TECELASQL_DELETECOMMAND_H

#include <mutex>

#include "../Command.h"
#include "../../HashTable/HashTable.h"
#include "../../exceptions.h"


class DeleteCommand : public Command {
public:
    explicit DeleteCommand(std::string key):
            key(std::move(key))
            {};

    ~DeleteCommand() override = default;

    std::string toStr();

    std::string execute() override;

private:
    const std::string key;

    std::recursive_mutex _mx;

};


#endif //TECELASQL_DELETECOMMAND_H