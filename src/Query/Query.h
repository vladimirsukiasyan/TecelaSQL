
#ifndef TECELASQL_QUERY_H
#define TECELASQL_QUERY_H

#include "../Command/Command.h"
#include "../Command/GetCommand/GetCommand.h"
#include "../Command/AddCommand/AddCommand.h"
#include "../Command/SetCommand/SetCommand.h"
#include "../Command/DeleteCommand/DeleteCommand.h"
#include "../Command/TouchCommand/TouchCommand.h"
#include "../Command/IncrCommand/IncrCommand.h"
#include "../Command/DecrCommand/DecrCommand.h"
#include "../Command/FlushAllCommand/FlushAllCommand.h"
#include "../Command/DisconnectCommand/DisconnetCommand.h"
#include "../utils.h"
#include <map>
#include <boost/algorithm/string.hpp>
#include <iostream>

const int ADD_COMMAND_HEADLINE_PARAMS_COUNT = 4;

class Query {
    METHOD method;
    Command *command = nullptr;

public:

    Query(){
        std::cout<<"Query()"<<std::endl;
    }

    ~Query(){
        std::cout<<"~Query()"<<std::endl;
        delete command;
    }

    bool isHeadLineReceived = false;

    Command *getCommand();

    void parseHeadLine(const std::string &headBuffer);

    bool hasToSendBodyLine();

    void setCommandValue(const std::string bodyBuffer);
};


#endif //TECELASQL_QUERY_H