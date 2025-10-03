#include "server.hpp"
#include "libtslog.hpp"
#include "client_handler.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>

Server::Server(const std::string &host, uint16_t port, const std::string &www_root, int backlog)
    : host_(host), port_(port), www_root_(www_root), backlog_(backlog), listen_fd_(-1), running_(false) {}

Server::~Server() { stop(); }

void Server::start() {
    if (running_) return;

    listen_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd_ < 0) throw std::runtime_error("Erro ao criar socket");

    int opt = 1;
    setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd_, (sockaddr*)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("Erro no bind");

    if (listen(listen_fd_, backlog_) < 0)
        throw std::runtime_error("Erro no listen");

    running_ = true;
    TsLogger::getInstance().log("Servidor iniciado na porta " + std::to_string(port_));
    std::thread(&Server::accept_loop, this).detach();
}

void Server::stop() {
    running_ = false;
    if (listen_fd_ >= 0) close(listen_fd_);
}

bool Server::isRunning() const { return running_; }

void Server::accept_loop() {
    while (running_) {
        sockaddr_in client_addr{};
        socklen_t len = sizeof(client_addr);
        int client_fd = accept(listen_fd_, (sockaddr*)&client_addr, &len);
        if (client_fd < 0) continue;
        std::thread(&Server::handle_client, this, client_fd).detach();
    }
}

void Server::handle_client(int client_fd) {
    handle_client_connection(client_fd, www_root_);
    close(client_fd);
}
