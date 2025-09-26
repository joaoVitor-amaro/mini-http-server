# 🌐 Mini Servidor Web (HTTP)

Projeto desenvolvido para a disciplina LPII — Programação Concorrente (C/C++)
Tema escolhido: B — Mini Servidor Web HTTP

# 📌 Etapa 1 — Logger + Arquitetura
Nesta etapa foi implementada a biblioteca libtslog, um logger thread-safe que garante gravação concorrente de mensagens em arquivo e console.
Também foi definida a arquitetura inicial do projeto, com diretórios para include/, src/, tests/, logs/ e diagrams/.

# 📂 Estrutura de Pasta

mini-http-server/
├── include/             # Headers (.hpp)
│   ├── libtslog.hpp
│   ├── server.hpp
│   ├── client_handler.hpp
│   ├── config.hpp
│
├── src/                 # Código-fonte (.cpp)
│   ├── libtslog.cpp
│   ├── main.cpp
│   ├── server.cpp
│   ├── client_handler.cpp
│
├── tests/               # Testes
│   ├── test_logger.cpp
│
├── logs/                # Saída dos logs
│   ├── server.log
│
├── diagrams/            # Diagramas de arquitetura
│   ├── diagramaEtapa1.md
│
├── CMakeLists.txt
└── README.md

O que cada pasta/arquivo contém:
    - CMakeLists.txt: Define a configuração do projeto: compila a biblioteca libtslog.a, o executável server e o binário de testes test_logger.
    
    - include/ - Headers públicos do projeto:
        - libtslog.hpp — API de logging usada pelo servidor (níveis de log, macros, sinks).
        - server.hpp — Interface do servidor HTTP (inicialização, loop principal, shutdown).
        - client_handler.hpp — Declarações para lidar com conexões individuais (parsing da requisição, envio de resposta).
        - config.hpp — Estruturas e constantes de configuração (porta, paths de log, limites de threads).
    
    - src/ - Implementações: 
        - libtslog.cpp — Loop da thread de logging e escrita em sinks (console/arquivo). 
        - server.cpp — Implementação do servidor: socket, bind/listen, loop aceitando conexões.
        - client_handler.cpp — Função que atende cada cliente em thread separada, parseia requisição e monta resposta HTTP.
        - main.cpp — Ponto de entrada: lê config, inicia logger e servidor, trata sinal de término.
    
    - diagrams/diagramaEtapa1.md: Documentação em Markdown com diagrama explicando o fluxo de execução da Etapa 1

    - logs/server.log: Arquivo de log gerado em runtime


# ⚙️ Compilação 
Requisitos: Linux, CMake ≥ 3.10, Compilador g++ ≥ 9.0

Cria a pasta build: mkdir build && cd build<br>
Gera os arquivos do build: cmake ..<br>
Compila: make 

# ▶️ Execução
./server           # inicia o servidor HTTP<br>
./test_logger      # roda o teste do logger

