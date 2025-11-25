#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "perfil.h"
#include "ui.h"
#include "receitas.h"

#define FRAME_RATE_MS 50

int main() {
    Player player;

    keyboardInit();
    screenInit(1);
    timerInit(FRAME_RATE_MS);

    tela_inicial();
    mostrarTelaRanking();
    historia(&player);

   int jogando = 1;
    while (jogando) {
        
        int idFase = menuSelecaoFase(&player);

        if (idFase == -1) {
            jogando = 0; 
        } else {
            Receita faseAtual;
            
            faseAtual.ingredientes = NULL;

            if (carregarFase(idFase, &faseAtual)) {
                jogarFase(&faseAtual, &player);
                liberarReceita(&faseAtual);
            if(player.xp >= 1750){
        jogoConcluido(&player);
    }
            }
        }
    }

    keyboardDestroy();
    screenDestroy();

    return 0;
}