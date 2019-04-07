//
// Created by vladimir on 07.04.19.
//

#ifndef TECELASQL_SOCKET_H
#define TECELASQL_SOCKET_H


#include <string>

class Socket {
public:
    Socket();

    Socket(int sd): _sd(sd){}

    ~Socket();

    std::string recv();

    void send(std::string&);

    void close();

private:
     int _sd;
};


#endif //TECELASQL_SOCKET_H
