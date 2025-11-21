#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "perfil.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define ARQUIVO_PERFIL "stats.txt"
#define MAX_LINHA 256

void carregarArquivo(char *inputNome, Player *p){

    FILE *arquivo = fopen(ARQUIVO_PERFIL, "r");
    char linha[MAX_LINHA];
    char linhaXP[MAX_LINHA];
    int numero_linha = 0;
    int encontrado = 0;

    if(arquivo != NULL){
        fclose(arquivo);
    } else{
        arquivo = fopen(ARQUIVO_PERFIL, "w");
        if(arquivo) fclose(arquivo);
    }

    arquivo = fopen(ARQUIVO_PERFIL, "r");

    strcpy(p -> nome, inputNome);

    char nomeLower[MAX_LINHA];
    strcpy(nomeLower, inputNome);
    strlwr(nomeLower);

    p -> xp = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        numero_linha++;
        linha[strcspn(linha, "\n")] = 0;

        if(fgets(linhaXP, sizeof(linhaXP), arquivo) == NULL){
                break;
        }

        char linhaArquivoLower[MAX_LINHA];
        strcpy(linhaArquivoLower, linha);
        strlwr(linhaArquivoLower);

        if (strcmp(strlwr(linha), nomeLower) == 0) {
            p -> xp = atoi(linhaXP);
            encontrado = 1;
            break;
        }

    }

    fclose(arquivo);

    if(encontrado == 0){
        arquivo = fopen(ARQUIVO_PERFIL, "a");
        if(arquivo){
            fprintf(arquivo, "%s\n0\n", inputNome);
            fclose(arquivo);
        }
    }


}

