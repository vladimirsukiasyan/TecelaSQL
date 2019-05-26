//
// Created by vladimir on 13.04.19.
//

#ifndef TECELASQL_QUERY_H
#define TECELASQL_QUERY_H

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <any>

#include "../Command/Command.h"
#include "../Command/GetCommand/GetCommand.h"
#include "../Command/AddCommand/AddCommand.h"
#include "../Command/SetCommand/SetCommand.h"
#include "../Command/DeleteCommand/DeleteCommand.h"
#include "../Command/TouchCommand/TouchCommand.h"
#include "../Command/IncrCommand/IncrCommand.h"
#include "../Command/DecrCommand/DecrCommand.h"
#include "../Command/FlushAllCommand/FlushAllCommand.h"
#include "../utils.h"

const int ADD_COMMAND_HEADLINE_PARAMS_COUNT = 4;
const int SET_COMMAND_HEADLINE_PARAMS_COUNT = 4;
const int GET_COMMAND_HEADLINE_PARAMS_COUNT = 2;
const int DELETE_COMMAND_HEADLINE_PARAMS_COUNT = 2;

class Query {
    METHOD _method;
public:
    METHOD get_method() const;

private:
    Command *command = nullptr;
    std::map<std::string,std::any> _params;

public:
    explicit Query();

    ~Query();

    Command *getCommand();

    void parseHeadLine(const std::string &headBuffer);

    bool hasToSendValueLine() const;

    void setCommandValue(const std::string &valueBuffer);
};


#endif //TECELASQL_QUERY_H
