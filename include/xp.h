#ifndef XP_H  
#define XP_H  

#include "perfil.h" 

static const int xpPorNivel[];
int xpParaProximoNivel(int nivel);
void atualizarXP(int xpGanho, Player *p);
int calcularNivel(int xp);


#endif
