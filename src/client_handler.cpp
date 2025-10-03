#include "client_handler.hpp"
#include "libtslog.hpp"
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

static void send_response(int client_fd, int code, const std::string &status,
                          const std::string &body, const std::string &ctype="text/plain") {
    std::ostringstream oss;
    oss << "HTTP/1.0 " << code << " " << status << "\r\n";
    oss << "Content-Length: " << body.size() << "\r\n";
    oss << "Content-Type: " << ctype << "\r\n";
    oss << "Connection: close\r\n\r\n";
    oss << body;
    send(client_fd, oss.str().c_str(), oss.str().size(), 0);
}

void handle_client_connection(int client_fd, const std::string &www_root) {
    char buf[4096];
    int n = recv(client_fd, buf, sizeof(buf)-1, 0);
    if (n <= 0) return;

    // cria string com tamanho exato dos bytes lidos
    std::string req(buf, n);

    // parse da primeira linha HTTP
    std::istringstream iss(req);
    std::string method, url, proto;
    iss >> method >> url >> proto;

    TsLogger::getInstance().log("Requisição recebida: " + method + " " + url);

    if (method != "GET") {
        send_response(client_fd, 405, "Method Not Allowed", "Only GET supported");
        return;
    }

    if (url == "/") url = "/index.html";
    std::string fullpath = www_root + url;

    std::ifstream ifs(fullpath, std::ios::binary);
    if (!ifs) {
        send_response(client_fd, 404, "Not Found", "Arquivo não encontrado");
        TsLogger::getInstance().log("404: " + fullpath);
        return;
    }

    std::ostringstream body;
    body << ifs.rdbuf();

    send_response(client_fd, 200, "OK", body.str(), "text/html");
    TsLogger::getInstance().log("200: " + fullpath);
}

