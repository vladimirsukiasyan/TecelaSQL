//
// Created by vladimir on 13.04.19.
//

#ifndef TECELASQL_COMMAND_H
#define TECELASQL_COMMAND_H

#include <map>
#include <utility>
#include <cstddef>

class Command {
public:
    virtual std::string execute() = 0;

    Command() = default;

    virtual ~Command() = default;
};


#endif //TECELASQL_COMMAND_H
