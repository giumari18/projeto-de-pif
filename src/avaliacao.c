#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "perfil.h"
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "xp.c"


int estrelas;

 
void definirEstrelas(Player *p, int quantidadeAcertos, int totalQuestoes) {

    float proporcao = (float)quantidadeAcertos / totalQuestoes;

    if (proporcao == 0) {
        estrelas = 0;
        
    } else if (proporcao >= 0) {
        estrelas = 1;
    } else if (proporcao >= 0.20) {
        estrelas = 2;
    } else if (proporcao >= 0.40) {
        estrelas = 3;
    } else if (proporcao > 0.60) {
        estrelas = 4;
    } else if( proporcao == 1.0) {
        estrelas = 5;
    }
    
    mostrarEstrelas(p, estrelas);
}


void mostrarEstrelas(Player *p, int estrelas) {


    if (estrelas == 0) {
        centralizar_texto("☆ ☆ ☆ ☆ ☆", 19);
    } else if (estrelas == 1) {
        centralizar_texto("★ ☆ ☆ ☆ ☆", 19);
    } else if (estrelas == 2) {
        centralizar_texto("★ ★ ☆ ☆ ☆", 19);
    } else if (estrelas == 3) {
        centralizar_texto("★ ★ ★ ☆ ☆", 19);
    } else if (estrelas == 4) {
        centralizar_texto("★ ★ ★ ★ ☆", 19);
    } else if( estrelas == 5) {
        centralizar_texto("★ ★ ★ ★ ★", 19);
    
}


