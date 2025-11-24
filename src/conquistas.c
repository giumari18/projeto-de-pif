#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perfil.h"
#include "conquistas.h"



#define ARQUIVO_PROGRESSO "progresso.csv"
#define MAX_LINHA 1024


void remove_newline(char *str) {
    str[strcspn(str, "\n")] = 0;
}

void salvarEstrelasFase(char *nomeJogador, char *nomeFase, int novasEstrelas) {
    FILE *arquivo = fopen(ARQUIVO_PROGRESSO, "r");
    FILE *temp = fopen("temp_progresso.csv", "w");

    if (arquivo == NULL) {
        arquivo = fopen(ARQUIVO_PROGRESSO, "w");
        if (arquivo) {
            fprintf(arquivo, "%s,%s,%d\n", nomeJogador, nomeFase, novasEstrelas);
            fclose(arquivo);
        }
        if (temp) fclose(temp);
        remove("temp_progresso.csv");
        return;
    }

    if (temp == NULL) {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(arquivo);
        return;
    }

    char linha[MAX_LINHA];
    char linhaCopia[MAX_LINHA];
    int encontrou = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        strcpy(linhaCopia, linha); 
        remove_newline(linhaCopia);

        char *csvNome = strtok(linhaCopia, ",");
        char *csvFase = strtok(NULL, ",");
        char *csvEstrelas = strtok(NULL, ",");


        if (csvNome && csvFase && 
            strcmp(csvNome, nomeJogador) == 0 && 
            strcmp(csvFase, nomeFase) == 0) {
            
            fprintf(temp, "%s,%s,%d\n", nomeJogador, nomeFase, novasEstrelas);
            
            
            encontrou = 1;
        } else {
            fprintf(temp, "%s", linha);
        }
    }


    if (!encontrou) {
        fprintf(temp, "%s,%s,%d\n", nomeJogador, nomeFase, novasEstrelas);
    }

    fclose(arquivo);
    fclose(temp);

    remove(ARQUIVO_PROGRESSO);
    rename("temp_progresso.csv", ARQUIVO_PROGRESSO);
}