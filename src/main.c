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
    Receita receita;

    keyboardInit();
    screenInit(1);
    timerInit(FRAME_RATE_MS);

    tela_inicial();
    historia(&player);

   int jogando = 1;
    while (jogando) {
        
        // Seleciona a fase
        int idFase = menu_selecao_fase();

        if (idFase == -1) {
            jogando = 0; // Sai do jogo se escolher sair/erro
        } else {
            // Carrega a receita escolhida
            Receita faseAtual;
            if (carregarFase(idFase, &faseAtual)) {

                jogarFase(&faseAtual, &player);
                
            }
        }
    }


    keyboardDestroy();
    screenDestroy();

    return 0;
}
