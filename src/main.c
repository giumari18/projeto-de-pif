#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "perfil.h"
#include "ui.h"
#import "receitas.h"

#define FRAME_RATE_MS 50


int main() {
    Player player;
    Receita receita;

    keyboardInit();
    screenInit(1);
    timerInit(FRAME_RATE_MS);

    tela_inicial();
    historia(&player);

    // 1. Chama o menu bonito da UI
    int idFase = menu_selecao_fase();

    // Se retornou -1, deu erro ou saiu
    if (idFase == -1) {
        screenDestroy();
        return 0;
    }


    keyboardDestroy();
    screenDestroy();

    return 0;
}
