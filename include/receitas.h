#ifndef RECEITAS_H
#define RECEITAS_H

typedef struct {
    char premissas[5][100];
    char alternativas[4][100];
    char alternativaCerta[100];
} Ingrediente;

typedef struct {
    char nome[50];
    Ingrediente *ingredientes;
    int quantidadeIngredientes;
    int nivel;
} Receita;

int listarNomesDasFases();

int carregarFase(int idFase, Receita *r);

void liberarReceita(Receita *r);

#endif
