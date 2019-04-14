//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_ADDCOMMAND_H
#define TECELASQL_ADDCOMMAND_H

#include "../Command.h"

class AddCommand: public Command{
public:
    AddCommand(std::map<std::string, std::string> params){
        //инициализация команды
    }

    void execute() override;

private:
    std::map<std::string,std::string> params;
};


#endif //TECELASQL_ADDCOMMAND_H
