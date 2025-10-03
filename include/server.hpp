#pragma once
#include <string>
#include <thread>
#include <vector>
#include <atomic>

class Server {
public:
    Server(const std::string &host, uint16_t port, const std::string &www_root, int backlog = 10);
    ~Server();

    void start();
    void stop();
    bool isRunning() const;

private:
    std::string host_;
    uint16_t port_;
    std::string www_root_;
    int backlog_;
    int listen_fd_;
    std::atomic<bool> running_;
    std::vector<std::thread> threads_;

    void accept_loop();
    void handle_client(int client_fd);
};
