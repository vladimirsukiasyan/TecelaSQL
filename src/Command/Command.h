//
// Created by vladimir on 13.04.19.
//

#ifndef TECELASQL_COMMAND_H
#define TECELASQL_COMMAND_H

#include <map>
#include <utility>
#include <cstddef>
#include "../utils.h"

class Command {
public:
    virtual void execute() = 0;
    Command() = default;
};


#endif //TECELASQL_COMMAND_H
