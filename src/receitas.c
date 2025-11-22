#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receitas.h"

#define ARQUIVO_RECEITAS "recipes.csv"
#define MAX_LINHA 4096


int listarNomesDasFases() {
    FILE *arquivo = fopen(ARQUIVO_RECEITAS, "r");
    if (!arquivo) return 0;

    char linha[MAX_LINHA];
    int contador = 0;

    printf("\n=== MENU DE RECEITAS ===\n");
    
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        if (strlen(linha) == 0) continue;

        char *nome = strtok(linha, ",");
        if (nome) {
            printf("%d. %s\n", contador + 1, nome);
            contador++;
        }
    }
    
    fclose(arquivo);
    return contador;
}


int carregarFase(int idFase, Receita *r) {
    FILE *arquivo = fopen(ARQUIVO_RECEITAS, "r");
    if (!arquivo) return 0;

    char linha[MAX_LINHA];
    int linhaAtual = 0;
    int encontrou = 0;


    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strlen(linha) < 2) continue;

        if (linhaAtual == idFase) {
            linha[strcspn(linha, "\n")] = 0;
            encontrou = 1;
            
            
            // 1. Nome
            char *token = strtok(linha, ",");
            if(token) strcpy(r->nome, token);

            // 2. Quantidade
            token = strtok(NULL, ",");
            if(!token) break;
            int qtd = atoi(token);
            if (qtd > 10) qtd = 10;
            r->quantidadeIngredientes = qtd;

            // 3. Loop dos Ingredientes
            int i;
            for (i = 0; i < qtd; i++) {
                Ingrediente *ing = &r->ingredientes[i];
                
                // Premissas
                for(int p=0; p<4; p++) {
                    token = strtok(NULL, ",");
                    if(token) strcpy(ing->premissas[p], token);
                }
                // Alternativas
                for(int a=0; a<4; a++) {
                    token = strtok(NULL, ",");
                    if(token) strcpy(ing->alternativas[a], token);
                }
                // Resposta
                token = strtok(NULL, ",");
                if(token) strcpy(ing->alternativaCerta, token);
            }
            
            break; 
        }
        linhaAtual++;
    }

    fclose(arquivo);
    return encontrou;
}