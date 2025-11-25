#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "perfil.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"


// XP necessário para cada nível

// 1 - Commis chef - 0 xp
// 2- Chef de Partie - 300 xp
// 3 - Sous Chef - 750 xp
// 4 - Chef de Cuisine - 1250 xp


static const int xpPorNivel[] = { 0, 300, 750, 1250};

#define AQRUIVO_PERFIL "stats.txt"
#define ARQUIVO_TEMPORARIO "stats_temp.txt"
#define MAX_LINHA 256


char *toLower(char *c);

int xpParaProximoNivel(int nivel) {
    
    if(nivel <= 1) return xpPorNivel[0];
    if(nivel > 4) return xpPorNivel[3];
    return xpPorNivel[nivel - 1];
}


int _recursaoNivel(int xp, int nivelAtual) {

    int nivelMaximo = 4;

    if(nivelAtual >= nivelMaximo) {
        return nivelMaximo;
    }

    int proximoNivel = nivelAtual + 1;
    int indiceProximo = proximoNivel - 1;

    if(xp >= xpPorNivel[indiceProximo]){

        return _recursaoNivel(xp, proximoNivel);
    }

    return nivelAtual;
    
}


int calcularNivel(int xp) {
    return _recursaoNivel(xp, 1);
}



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
