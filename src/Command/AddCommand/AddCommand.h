//
// Created by vladimir on 14.04.19.
//

#ifndef TECELASQL_ADDCOMMAND_H
#define TECELASQL_ADDCOMMAND_H

#include <iostream>
#include "../Command.h"


class AddCommand: public Command{
public:
    //инициализация команды
    AddCommand(std::string &key,
               long long exptime,
               long long length
               ):
               key(key),
               exptime(exptime),
               length(length),
               value(nullptr)
               {
                   std::cout<<"AddCommand()"<<std::endl;
               }

   ~AddCommand() override {
       std::cout<<"~AddCommand()"<<std::endl;
       delete value;
    }
    void execute() override;

    void setValue(std::byte *value);

private:
    const std::string key;
    long long exptime;
    long long length;
    std::byte *value;
};


#endif //TECELASQL_ADDCOMMAND_H
