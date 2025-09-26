#include "libtslog.hpp"

int main() {
    // Inicializa o logger e escreve uma mensagem
    TsLogger::getInstance().log("Servidor iniciado (Etapa 1).");

    return 0;
}
