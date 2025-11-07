#include <stdio.h>
#include <string.h>
#include "cli_lib.h"

void saudar(const char *nome) {
    printf("Olá, %s! Bem-vindo à sua CLI.\n", nome);
}

int processar_comando(const char *comando) {
    if (strcmp(comando, "ajuda") == 0) {
        printf("Comandos disponíveis: ajuda, status, sair.\n");
        return 0;
    } else if (strcmp(comando, "sair") == 0) {
        printf("Saindo...\n");
        return 1; // Indicador para sair
    }
    printf("Comando '%s' não reconhecido.\n", comando);
    return -1; // Indicador de erro
}