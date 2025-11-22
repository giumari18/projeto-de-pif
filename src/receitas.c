#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "receitas.h"



#define ARQUIVO_RECEITAS "recipes.csv"
#define MAX_LINHA 256
#define MAX_INGREDIENTES 10
#define MAX_PREMISSAS 4



void carregarReceitas(Receita receitas[], int *linhaReceita) {

    FILE *arquivo = fopen(ARQUIVO_RECEITAS, "r");

    if (arquivo == NULL) {
        *linhaReceita = 0;
        return;
    }

    char linha[MAX_LINHA];
    int r = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {

        linha[strcspn(linha, "\n")] = 0;
        if (strlen(linha) == 0) continue; 

        char *token = strtok(linha, ",");
        if (!token) continue;

        
        strcpy(receitas[r].nome, token);

        int i = 0; 
        while ((token = strtok(NULL, ",")) && i < MAX_INGREDIENTES) {

            Ingrediente *ing = &receitas[r].ingredientes[i];
            memset(ing, 0, sizeof(Ingrediente));

            
            strcpy(ing->nome, token);

            int p = 0;
            
            for (; p < MAX_PREMISSAS; p++) {
                token = strtok(NULL, ",");
                if (!token || strlen(token) == 0) break;
                strcpy(ing->premissas[p], token);
            }
            ing->quantidadePremissas = p;

            
            token = strtok(NULL, ",");
            if (token && strlen(token) > 0)
                strcpy(ing->alternativaCerta, token);

            i++;
        }
        receitas[r].quantidadeIngredientes = i;
        r++;
    }
    *linhaReceita = r;
    fclose(arquivo);
}
