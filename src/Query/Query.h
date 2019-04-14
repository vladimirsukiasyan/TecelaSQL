//
// Created by vladimir on 13.04.19.
//

#ifndef TECELASQL_QUERY_H
#define TECELASQL_QUERY_H


class Query {
public:
    Command* getCommand();
private:
    void parseRequest(std::string request);
    //прочие функции для реализации getCommand()
};


#endif //TECELASQL_QUERY_H
