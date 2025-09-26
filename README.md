# 🌐 Mini Servidor Web (HTTP)

Projeto desenvolvido para a disciplina LPII — Programação Concorrente (C/C++)
Tema escolhido: B — Mini Servidor Web HTTP

# 📌 Etapa 1 — Logger + Arquitetura
Nesta etapa foi implementada a biblioteca libtslog, um logger thread-safe que garante gravação concorrente de mensagens em arquivo e console.
Também foi definida a arquitetura inicial do projeto, com diretórios para include/, src/, tests/, logs/ e diagrams/.


# Diagrama da Etapa 1

![Diagrama da Etapa 1](/diagrams/DiagramaEtapa1.png)

# Fluxo de Dados

   - Cliente HTTP: envia uma requisição GET para o servidor (ex.: navegador ou curl).
   - Socket Servidor: aceita a conexão de entrada.
   - Thread (ClientHandler): para cada conexão, uma thread (ou do pool) é criada para processar a requisição.
   - Processa GET: a thread lê o arquivo requisitado do diretório www/.
   - Resposta HTTP: a resposta é enviada de volta ao cliente.
   - Logger (libtslog): todas as operações são registradas de forma concorrente no log. 


# 📂 Estrutura de Pasta

```text
mini-http-server/
├── include/     
│   ├── libtslog.hpp     
│   ├── server.hpp          
│   ├── client_handler.hpp  
│   └── config.hpp          
├── src/            
│   ├── libtslog.cpp        
│   ├── main.cpp            
│   ├── server.cpp          
│   └── client_handler.cpp  
├── tests/           
│   └── test_logger.cpp   
├── logs/             
│   └── server.log
├── diagrams/         
│   └── diagramaEtapa1.png
├── CMakeLists.txt   
└── README.md   
```     

### Arquivos de configuração

- **CMakeLists.txt**: Define a configuração do projeto, incluindo a compilação da biblioteca `libtslog.a`, do executável `server` e do binário de testes `test_logger`.

### Diretório `include/` — Headers públicos do projeto

- **libtslog.hpp** — API de logging usada pelo servidor (níveis de log, macros, sinks).  
- **server.hpp** — Interface do servidor HTTP (inicialização, loop principal, shutdown).  
- **client_handler.hpp** — Declarações para lidar com conexões individuais (parsing da requisição, envio de resposta).  
- **config.hpp** — Estruturas e constantes de configuração (porta, paths de log, limites de threads).  

### Diretório `src/` — Implementações

- **libtslog.cpp** — Loop da thread de logging e escrita em sinks (console/arquivo).  
- **server.cpp** — Implementação do servidor: socket, bind/listen, loop aceitando conexões.  
- **client_handler.cpp** — Função que atende cada cliente em thread separada, parseia requisição e monta resposta HTTP.  
- **main.cpp** — Ponto de entrada: lê config, inicia logger e servidor, trata sinais de término.  

### Diretório `diagrams/`

- **diagramaEtapa1.png** — Imagem do diagrama.  

### Diretório `logs/`

- **server.log** — Arquivo de log gerado em runtime.
#

# ⚙️ Compilação 
Requisitos: Linux, CMake ≥ 3.10, Compilador g++ ≥ 9.0

Cria a pasta build: mkdir build && cd build<br>
Gera os arquivos do build: cmake ..<br>
Compila: make 

#
# ▶️ Execução
Inicia o servidor HTTP: ./server  
Roda o teste do logger: ./test_logger

