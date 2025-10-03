#include "libtslog.hpp"
#include "server.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

int main(int argc, char **argv) {
    int port = 8080;
    std::string www_root = "./www";

    if (argc >= 2) port = std::stoi(argv[1]);
    if (argc >= 3) www_root = argv[2];

    if (!std::filesystem::exists(www_root)) {
        std::filesystem::create_directory(www_root);
        std::ofstream("./www/index.html") << "<h1>Servidor HTTP Etapa 2</h1>\n";
    }

    TsLogger::getInstance().log("Iniciando servidor HTTP...");
    Server server("0.0.0.0", port, www_root);
    server.start();

    std::cout << "Pressione ENTER para parar..." << std::endl;
    std::string s;
    std::getline(std::cin, s);
    server.stop();
}
