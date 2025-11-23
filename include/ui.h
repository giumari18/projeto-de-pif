#ifndef UI_H
#define UI_H
#include "perfil.h"
#include "receitas.h"

void tela_inicial();
void historia(Player *p);
int menuSelacaoFase();

int rodarQuestaoIngrediente(Ingrediente *ing, int indice, int total);

void mostrarTelaAcerto(char *resposta, int xpGanho);
void mostrarTelaErro(char *escolha, char *correta);
void mostrarFimFase(char *nomeReceita);
void jogarFase(Receita *r, Player *p);

#endif
