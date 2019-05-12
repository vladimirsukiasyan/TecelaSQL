//
// Created by vladimir on 05.05.19.
//
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>

using namespace boost::asio;

ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 12000);
boost::asio::io_service service;

struct talk_to_svr {
    talk_to_svr() :
            sock_(service) {}

    void connect(const ip::tcp::endpoint &ep) {
        sock_.connect(ep);
    }

    void loop() {
        while (true) {
            write();
            read_answer();
        }
    }

    void read_answer() {
        size_t bytes_transferred = sock_.read_some(buffer(buff_));
        std::string response(buff_,bytes_transferred);
        std::cout << response << std::endl;
    }

    void write() {
        std::string query;
        getline(std::cin, query);
        sock_.write_some(buffer(query));
    }

private:
    ip::tcp::socket sock_;
    enum {
        max_msg = 1024
    };
    char buff_[max_msg];
};


void run_client() {
    talk_to_svr client;
    try {
        client.connect(ep);
        client.loop();
    }
    catch (boost::system::system_error &err) {
        std::cout << "client terminated " << std::endl;
    }
}

int main() {
    run_client();
}