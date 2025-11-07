#include <stdio.h>
#include <string.h>
#include "cli_lib.h" // Inclui o cabeçalho da sua biblioteca

int main(int argc, char *argv[]) {
    // Exemplo de uso
    saudar("Usuário");

    if (argc > 1) {
        // Pega o primeiro argumento da linha de comando
        char *comando = argv[1];
        processar_comando(comando);
    } else {
        printf("Por favor, forneça um comando (ex: ./build/cli_exec ajuda).\n");
    }

    return 0;
}