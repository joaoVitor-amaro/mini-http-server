# Relatório Final —  Mini Servidor Web (HTTP)

**Aluno**: João Vitor Amaro de Melo<br>
**Disciplina**: Linguagem de Programação II
**Projeto**: Mini Servidor Web

## 1. Diagrama de sequência cliente-servidor

```bash
+---------+       +-----------+       +---------------+       +--------+
| Cliente |       | Servidor  |       | Thread Worker |       | Logger |
+---------+       +-----------+       +---------------+       +--------+
     |                  |                     |                   |
     | ---- TCP Conn -->|                     |                   |
     |                  |-- accept() -------->|                   |
     |                  |-- cria thread ----->|                   |
     | ---- GET / ------>                     |                   |
     |                  |                     |-- lê arquivo ----> FS
     |                  |                     |
     |                  |                     |-- 200 OK/404 ---->|
     |                  |                     |-- log ----------->|
     |                  |                     |-- fecha conexão -->|

```

## Fluxo do Cliente-Servidor
- Cliente → Servidor: Conexão via socket TCP
- Servidor: Aceita a conexão e cria uma thread dedicada (worker)
- Thread Worker → Sistema de Arquivos: Busca o arquivo solicitado no diretório www_root
- Thread Worker → Cliente: Retorna resposta HTTP (200 OK + arquivo, ou 404 Not Found)
- Thread Worker → Logger: Registra a requisição e o status da resposta em server.log
- Thread Worker: Fecha a conexão com o cliente

# Mapeamento requisitos → código
- Threads (std::thread): O servidor cria uma thread por conexão (handleClient em server.cpp).
- Exclusão mútua (std::mutex): Usado em server.cpp para proteger a lista de threads ativas.
- Semáforos / condvars: Não implementado explicitamente, mas o backlog do listen() limita conexões pendentes (fila de espera). Pode ser estendido para ThreadSafeQueue.
- Monitores: Classe Server encapsula sincronização e estatísticas (atomic counters).
- Gerenciamento de recursos: Uso de RAII em std::thread e std::atomic, fechamento explícito de socket.
- Tratamento de erros: Respostas HTTP de sucesso (`200 OK`) e de erro (`404 Not Found`, `500 Internal Server Error`) são geradas e enviadas ao cliente. Erros também são registrados no log.
- Logging concorrente: libtslog garante exclusão mútua ao gravar em logs/server.log.
- Documentação / Build: CMakeLists.txt funcional, README.md atualizado, testes em tests/.

## Análise crítica com IA
### Possíveis problemas de concorrência

- **Race Condition:** acesso simultâneo à lista de threads (`worker_threads`).  
  Mitigação: uso de `std::mutex` ao inserir/joinar threads.

- **Deadlock:** não identificado, pois não há bloqueios aninhados.  
  Mitigação: design simples com bloqueios de curta duração.

- **Starvation:** pode ocorrer se muitas conexões simultâneas saturarem o sistema (muitos threads).  
  Mitigação: limitar backlog (`listen`) e, opcionalmente, usar um pool fixo de threads.

- **Exaustão de recursos:** muitas threads simultâneas podem consumir memória/CPU.  
  Mitigação: refatorar para thread-pool com `ThreadSafeQueue` e `std::condition_variable`.

### Sugestões de melhoria:
- Implementar thread-pool para controlar número máximo de threads.
- Adicionar limite de tamanho de resposta para evitar ataques com arquivos muito grandes.
- Melhorar segurança contra path traversal (já mitigado com std::filesystem::path, mas recomenda-se normalizar caminhos).
- Suporte opcional a keep-alive para reduzir custo de múltiplas conexões.

# Conclusão 
A Etapa 3 implementa um servidor HTTP/1.0 concorrente, capaz de servir arquivos de um diretório via requisições GET. O sistema utiliza threads para concorrência, exclusão mútua para consistência, logging thread-safe e estatísticas básicas. Foram discutidos riscos de concorrência e propostas melhorias futuras como uso de thread-pool.