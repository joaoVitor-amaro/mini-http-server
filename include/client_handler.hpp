#pragma once
#include <string>

// Lida com cada conexão individual
void handle_client_connection(int client_fd, const std::string &www_root);
