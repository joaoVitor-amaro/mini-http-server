#include "libtslog.hpp"
#include <thread>
#include <vector>

void worker(int id) {
    for (int i = 0; i < 5; i++) {
        TsLogger::getInstance().log("Thread " + std::to_string(id) + " - mensagem " + std::to_string(i));
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.emplace_back(worker, i);
    }
    for (auto &t : threads) t.join();
    return 0;
}
