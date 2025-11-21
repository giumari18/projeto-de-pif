#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "screen.h"
#include "keyboard.h"
#include "ui.h"
#include "perfil.h"

#define ARQUIVO_RANKING "ranking.csv"

void pintar_fundo(int largura, int altura, int cor_fundo) {
  screenSetColor(cor_fundo, cor_fundo);
  for (int y = 0; y < altura; y++) {
    screenGotoxy(0, y);
    for (int x = 0; x < largura; x++) {
      printf(" ");
    }
  }
}

void centralizar_texto(const char *texto, int y) {
    int largura_tela = 80;
    int x = (largura_tela - strlen(texto)) / 2;
    if (x < 0) x = 0;
    screenGotoxy(x, y);
    printf("%s", texto);
}

void tela_inicial() {
    const char *arte[] = {
        " █████                          ███                                     █████                      █████████                       █████            ",
        "░░███                          ░░░                                     ░░███                      ███░░░░░███                     ░░███             ",
        " ░███         ██████   ███████ ████   ██████   ██████       ██████      ░███         ██████      ███     ░░░   ██████   ████████  ███████    ██████ ",
        " ░███        ███░░███ ███░░███░░███  ███░░███ ░░░░░███     ░░░░░███     ░███        ░░░░░███    ░███          ░░░░░███ ░░███░░███░░░███░    ███░░███",
        " ░███       ░███ ░███░███ ░███ ░███ ░███ ░░░   ███████      ███████     ░███         ███████    ░███           ███████  ░███ ░░░   ░███    ░███████ ",
        " ░███      █░███ ░███░███ ░███ ░███ ░███  ███ ███░░███     ███░░███     ░███      █ ███░░███    ░░███     ███ ███░░███  ░███       ░███ ███░███░░░  ",
        " ███████████░░██████ ░░███████ █████░░██████ ░░████████   ░░████████    ███████████░░████████    ░░█████████ ░░████████ █████      ░░█████ ░░██████ ",
        "░░░░░░░░░░░  ░░░░░░   ░░░░░███░░░░░  ░░░░░░   ░░░░░░░░     ░░░░░░░░    ░░░░░░░░░░░  ░░░░░░░░      ░░░░░░░░░   ░░░░░░░░ ░░░░░        ░░░░░   ░░░░░░  ",
        "",
        "Pressione ENTER para iniciar ou ESC para sair"
    };

    screenClear();
    pintar_fundo(150, 45, BLACK);
    screenSetColor(WHITE, BLACK);

    int y = 5;
    int linhas = sizeof(arte) / sizeof(arte[0]);

    for (int i = 0; i < linhas; i++) {
        centralizar_texto(arte[i], y++);
    }

    getchar();
}

int nome_valido(const char *nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isspace(nome[i])) return 1;
    }
    return 0;
}

void obter_nome_jogador(Player *p) {
    screenClear();
    pintar_fundo(150, 45, BLACK);

    int largura = 80;
    int y_nome = 10;
    int tentativa = 0;

    screenSetColor(WHITE, BLACK);
    centralizar_texto("Qual seu nome de chef?", y_nome);

    do {
        if (tentativa) {
            screenGotoxy(0, y_nome + 4);
            printf("%*s", largura, " "); 
        }

        int x_input = (largura - 30) / 2;

        screenGotoxy(x_input, y_nome + 2);
        printf("______________________________");

        screenGotoxy(x_input, y_nome + 2);
        screenSetColor(LIGHTGRAY, BLACK);
        
        fgets(p->nome, 50, stdin);
        
        screenSetColor(WHITE, BLACK);

        p->nome[strcspn(p->nome, "\n")] = '\0';

        if (!nome_valido(p->nome)) {
            screenSetColor(RED, BLACK);
            centralizar_texto("Nome invalido. Tente novamente.", y_nome + 4);
            screenSetColor(WHITE, BLACK);
        }

        tentativa = 1;

    } while (!nome_valido(p->nome));
}

void historia(Player *p) {
    screenClear();
    pintar_fundo(150, 45, BLACK);

    int y = 3;

    centralizar_texto("====================================================", y++);
    centralizar_texto("              LOGICA A LA CARTE                     ", y++);
    centralizar_texto("====================================================", y++);

    screenSetColor(LIGHTGRAY, BLACK);
    y++;

    centralizar_texto("Um dia, o professor Diego simplesmente desistiu.", y++);
    centralizar_texto("Largou a vida de tecnologia, saiu da CESAR School,", y++);
    centralizar_texto("e decidiu seguir sua verdadeira vocacao: a gastronomia.", y++);
    centralizar_texto("Diego possui habilidade culinaria, mas organizou seu", y++);
    centralizar_texto("livro de receitas utilizando logica e matematica.", y++);
    centralizar_texto("E cabe a VOCE ajuda-lo nessa nova jornada.", y++);

    screenSetColor(GREEN, BLACK);
    centralizar_texto("Pronto para comecar?", y + 2);
    screenSetColor(WHITE, BLACK);
    centralizar_texto("Pressione ENTER", y + 3);

    getchar();

    obter_nome_jogador(p);

    carregarArquivo(p->nome, p);

    char mensagem[120];
    sprintf(mensagem, "Bem-vinde, %s! (XP: %d). Pressione ENTER!", p->nome, p->xp);

    centralizar_texto(mensagem, 16);
    getchar();
}