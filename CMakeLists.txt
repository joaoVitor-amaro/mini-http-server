cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(MiniWebServer LANGUAGES CXX)

# Versão do C++ padrão
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Diretórios de include
include_directories(include)

# Biblioteca libtslog (logger thread-safe)
add_library(tslog STATIC
    src/libtslog.cpp
)

# Executável principal do servidor (por enquanto esqueleto)
add_executable(server
    src/main.cpp
    src/server.cpp
    src/client_handler.cpp
)

# Vincular biblioteca ao servidor
target_link_libraries(server tslog)

# Executável de teste do logger
add_executable(test_logger
    tests/test_logger.cpp
)

# Vincular biblioteca ao teste
target_link_libraries(test_logger tslog)
