#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perfil.h"
#include "ranking.h"

#define ARQUIVO_PERFIL "stats.txt"
#define MAX_LINHA 256

void ordenar_por_xp(Player lista[], int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
            if (lista[j].xp < lista[j+1].xp) {
                Player temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

int buscarRanking(Player listaDestino[], int tamanhoMaximo) {
    FILE *arquivo = fopen(ARQUIVO_PERFIL, "r");
    char linha[MAX_LINHA];
    char linhaXP[MAX_LINHA];
    int qtd = 0;

    if (!arquivo) return 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\n")] = 0;
        if (strlen(linha) == 0) continue;

        if (fgets(linhaXP, sizeof(linhaXP), arquivo) == NULL) break;

        if (qtd < tamanhoMaximo) {
            strcpy(listaDestino[qtd].nome, linha);
            listaDestino[qtd].xp = atoi(linhaXP);
            qtd++;
        }
    }
    fclose(arquivo);

    ordenar_por_xp(listaDestino, qtd);

    return qtd; 
}