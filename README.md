# 🌐 Mini Servidor Web (HTTP)

Projeto desenvolvido para a disciplina LPII — Programação Concorrente (C/C++)
Tema escolhido: B — Mini Servidor Web HTTP

# 📌 Etapa 3
Nesta etapa foi implementado:

 - Funcionalidades obrigatórias do tema concluídas
 - Logging integrado
 - Relatório final

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
│   ├── test_logger.cpp   
|   └── run_clients.sh   
├── logs/             
│   └── server.log
├── diagrams/         
│   └── diagramaEtapa1.png
├── CMakeLists.txt   
└── README.md   
```     

# ⚙️ Como rodar

### Pré-requisitos
   - Linux
   - CMake ≥ 3.10
   - g++ ≥ 9.0

### Compilação 

```bash
mkdir build && cd build
cmake ..
make 
```


### Execução
```bash
# Terminal 1 - Servidor(roda o servidor)
./server 8080 ./www

# Terminal 2 - Cliente 1 (requisição simples)
curl http://localhost:8080/

# Terminal 3 - Cliente 2
curl http://localhost:8080/index.html

# Terminal 4 - Ou usar o script de teste (a partir da pasta build/)
chmod +x tests/run_clients.sh
../tests/run_clients.sh 8080
```

### 🌐 Testar no navegador

É possível também abrir o navegador e acessar diretamente quando o servidor estiver rodando:<br>
👉 http://localhost:8080/index.html


## 🔗 Links Úteis

- [**Repositório do Projeto**](https://github.com/joaoVitor-amaro/mini-http-server)
- [**Relatório Técnico**](relatorio.md)
