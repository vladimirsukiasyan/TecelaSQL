//
// Created by vladimir on 05.05.19.
//

#ifndef TECELASQL_GETCOMMAND_H
#define TECELASQL_GETCOMMAND_H


#include "../Command.h"

class GetCommand: public Command{
public:
    //инициализация команды
    GetCommand(std::string &key): key(key) {}

    void execute() override;

private:
    const std::string key;
};




#endif //TECELASQL_GETCOMMAND_H
