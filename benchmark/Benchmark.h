//
// Created by dmitry on 24.05.19.
//

#ifndef TECELASQL_BENCHMARK_H
#define TECELASQL_BENCHMARK_H

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <ctime>
using namespace boost::asio;

ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 12000);
boost::asio::io_service service;

struct ServerBenchmark {
    ServerBenchmark() :
            sock_(service){}

    void connect(const ip::tcp::endpoint &ep);

    void loop();

    void get_request();

    void read_answer();

    void write_command();
    
    void write_value();
    
    void del_request();

private:
    ip::tcp::socket sock_;
    enum {
        max_msg = 1024
    };
    char buff_[max_msg];
};

#endif //TECELASQL_BENCHMARK_H
