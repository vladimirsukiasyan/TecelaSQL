#include <utility>

//
// Created by vladimir on 09.05.19.
//

#ifndef TECELASQL_EXCEPTIONS_H
#define TECELASQL_EXCEPTIONS_H

#include <exception>

class InvalidHeadLineException : public std::exception {

    std::string msg;

public:

    explicit InvalidHeadLineException(std::string msg="Invalid TextLine!"):
        msg(std::move(msg))
        {}

    const char *what() const throw() override {
        return msg.c_str();
    }
};

#endif //TECELASQL_EXCEPTIONS_H
