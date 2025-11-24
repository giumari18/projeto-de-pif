#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receitas.h"
#include <ctype.h>

#define ARQUIVO_RECEITAS "recipes.csv"
#define MAX_LINHA 4096

void trim(char *str) {
    char *end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0) return;

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    *(end + 1) = 0;
}

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

    r->ingredientes = NULL;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strlen(linha) < 2) continue;

        if (linhaAtual == idFase) {
            linha[strcspn(linha, "\n")] = 0;
            linha[strcspn(linha, "\r")] = 0;
            encontrou = 1;
            
            char *token = strtok(linha, ",");
            if(token) {
                trim(token);
                strcpy(r->nome, token);
            }

            token = strtok(NULL, ",");
            if(!token) break;
            trim(token);
            int qtd = atoi(token);
            
            r->quantidadeIngredientes = qtd;
            r->ingredientes = (Ingrediente *) malloc(qtd * sizeof(Ingrediente));

            if (r->ingredientes == NULL) {
                exit(1);
            }

            int i;
            for (i = 0; i < qtd; i++) {
                Ingrediente *ing = &r->ingredientes[i];
                
                for(int p=0; p<4; p++) {
                    token = strtok(NULL, ",");
                    if(token) {
                        trim(token);
                        strcpy(ing->premissas[p], token);
                    }
                }
                
                for(int a=0; a<4; a++) {
                    token = strtok(NULL, ",");
                    if(token) {
                        trim(token);
                        strcpy(ing->alternativas[a], token);
                    }
                }
                
                token = strtok(NULL, ",");
                if(token) {
                    trim(token);
                    strcpy(ing->alternativaCerta, token);
                }
            }
            
            break; 
        }
        linhaAtual++;
    }

    fclose(arquivo);
    return encontrou;
}

void liberarReceita(Receita *r) {
    if (r->ingredientes != NULL) {
        free(r->ingredientes);
        r->ingredientes = NULL;
        r->quantidadeIngredientes = 0;
    }
}
