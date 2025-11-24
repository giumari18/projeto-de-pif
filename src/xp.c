#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "perfil.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"


#define AQRUIVO_PERFIL "stats.txt"
#define ARQUIVO_TEMPORARIO "stats_temp.txt"
#define MAX_LINHA 256


char *toLower(char *c);


void atualizarXP(int xpGanho, Player *p){


    FILE *arquivo = fopen(AQRUIVO_PERFIL, "r");
    FILE *arquivoTemp = fopen(ARQUIVO_TEMPORARIO, "w");


    char linha[MAX_LINHA];
    char linhaXP[MAX_LINHA];
    int numeroLinha = 0;


    if(arquivo == NULL || arquivoTemp == NULL){
        return;
    }


    char nomePlayerLower[MAX_LINHA];
    strcpy(toLower(nomePlayerLower), p -> nome);


    while (fgets(linha, sizeof(linha), arquivo) != NULL) {

        numeroLinha++;
        linha[strcspn(linha, "\n")] = 0;

        if(fgets(linhaXP, sizeof(linhaXP), arquivo) == NULL){
                break;
        }


        char nomeArquivoLower[MAX_LINHA];
        strcpy(toLower(nomeArquivoLower), linha);
        

        if(strcmp(nomeArquivoLower, nomePlayerLower) == 0){

            int xpAtual = atoi(linhaXP);
            int xpAtualizado = xpAtual + xpGanho;

            fprintf(arquivoTemp, "%s\n%d\n", linha, xpAtualizado);

            p -> xp = xpAtualizado;

        } else{
            fprintf(arquivoTemp, "%s\n%s", linha, linhaXP);
        }
    }


    fclose(arquivo);
    fclose(arquivoTemp);

    remove(AQRUIVO_PERFIL);
    rename(ARQUIVO_TEMPORARIO, AQRUIVO_PERFIL);
}

int _recursaoNivel(int xp, int custoAtual) {

    if (xp < custoAtual) {
        return 1;
    }
    return 1 + _recursaoNivel(xp - custoAtual, custoAtual + 50);
}


int calcularNivel(int xp) {
    return _recursaoNivel(xp, 100);
}
