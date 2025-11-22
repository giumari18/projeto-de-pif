#ifndef RECEITAS_H
#define RECEITAS_H

typedef struct {
    char premissas[4][100];
    char alternativas[4][100];
    char alternativaCerta[100];
} Ingrediente;

typedef struct {
    char nome[50];
    Ingrediente ingredientes[10];
    int quantidadeIngredientes;
} Receita;

int listarNomesDasFases();

int carregarFase(int idFase, Receita *r);

#endif