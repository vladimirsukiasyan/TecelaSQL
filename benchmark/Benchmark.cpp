#include "Benchmark.h"

void ServerBenchmark::connect(const ip::tcp::endpoint &ep) {
    sock_.connect(ep);
}

void ServerBenchmark::loop() {
    write();
    while (true) {
        get_request();
        read_answer();
    }
    del_request();
}

void ServerBenchmark::get_request() {
    std::string query;
    query = "get 12";
    sock_.write_some(buffer(query));
}

void ServerBenchmark::del_request(){
    std::string query;
    query = "del 12";
    sock_.write_some(buffer(query));
}
void ServerBenchmark::read_answer() {
    size_t bytes_transferred = sock_.read_some(buffer(buff_));
    std::string response(buff_, bytes_transferred);
    std::cout << response << std::endl;
}

void ServerBenchmark::write() {
    std::string query;
    query = "add 12 100 10";
    sock_.write_some(buffer(query));
    query = "0123456789";
    buffer(query);
    std::cout << "Успешное добавление";
}

void run_client() {
    ServerBenchmark client;
    try {
        client.connect(ep);
        client.loop();
    }
    catch (boost::system::system_error &err) {
        std::cout << "client terminated " << std::endl;
    }
}

int main() {
    boost::asio::thread_pool pool(8);
    for (int i = 0; i < 8; i++)
        boost::asio::post(pool, [=] { run_client(); });
    pool.join();
    run_client();
    return 0;
};