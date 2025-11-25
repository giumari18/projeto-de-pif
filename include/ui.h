#ifndef UI_H
#define UI_H
#include "perfil.h"
#include "receitas.h"

void tela_inicial();
void historia(Player *p);
int menuSelecaoFase(Player *p);
void centralizar_texto(const char *texto, int y);
void mostrarTelaRanking();
int rodarQuestaoIngrediente(Ingrediente *ing, int indice, int total, const char *nomeReceita);

void mostrarTelaAcerto(char *resposta, int xpGanho);
void mostrarTelaErro(char *escolha, char *correta);
void mostrarFimFase(Player *p, char *nomeReceita, int quantidadeAcertos, int totalQuestoes);
void jogarFase(Receita *r, Player *p);

#endif
