#include <stdio.h>
#include <unistd.h>
#include "screen.h"
#include <string.h>
#include "keyboard.h"
#include <ctype.h>

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
        "                      ███ ░███                                                                                                                      ",
        "                     ░░██████                                                                                                                       ",
        "                      ░░░░░░                                                                                                                        ",
        "",
        "                      Pressione ENTER para iniciar ou ESC para sair"
    };

    screenClear();

    pintar_fundo(150, 45, BLACK);

    screenSetColor(WHITE, BLACK);

    int linhas = sizeof(arte) / sizeof(arte[0]);
    int y = 3;

    for (int i = 0; i < linhas; i++) {
        int x = (80 - strlen(arte[i])) / 2;
        if (x < 0) x = 0;
        screenGotoxy(x, y++);
        printf("%s", arte[i]);
    }

    getchar();
}

int nome_valido(const char *nome) {
  for (int i = 0; nome[i] != '\0'; i++) {
    if (!isspace(nome[i])) return 1;
  }
  return 0;
}

void historia(char *nome_jogador) {
    screenClear();
    pintar_fundo(150, 45, BLACK);

    int y = 3;

    screenGotoxy(20, y++);
    printf("====================================================");
    screenGotoxy(20, y++);
    printf("              LÓGICA À LA CARTE                     ");
    screenGotoxy(20, y++);
    printf("====================================================");

    screenSetColor(LIGHTGRAY, BLACK);
    y += 1;

    screenGotoxy(10, y++);
    printf("Um dia, o professor Diego simplesmente desistiu.");
    screenGotoxy(10, y++);
    printf("Largou a vida de tecnologia, saiu da CESAR School, e decidiu");
    screenGotoxy(10, y++);
    printf("seguir sua verdadeira vocação: a gastronomia.");
    screenGotoxy(10, y++);
    printf("Diego possui grande habilidade culinária, mas estruturou seu");
    screenGotoxy(10, y++);
    printf("livro de receitas de maneira um tanto singular...");
    screenGotoxy(10, y++);
    printf("utilizando premissas e relações lógico-matemáticas para estruturar");
    screenGotoxy(10, y++);
    printf("cada ingrediente e etapa do preparo.");
    screenGotoxy(10, y++);
    screenSetColor(GREEN, BLACK);
    printf("E cabe a VOCÊ auxiliar Diego em sua nova jornada como chef.");

    screenGotoxy(10, y + 2);
    screenSetColor(WHITE, BLACK);
    printf("Pronto para começar?");
    screenGotoxy(10, y + 3);
    printf("Pressione ENTER");
    getchar();

    screenClear();
    pintar_fundo(150, 45, BLACK);

    int largura_tela = 80;
    int y_nome = 10;

    const char *pergunta = "Qual seu nome de chef?";
    int x_pergunta = (largura_tela - strlen(pergunta)) / 2;
    screenGotoxy(x_pergunta, y_nome);
    printf("%s", pergunta);

    int tentativa = 0;
    do {
        if (tentativa) {
            screenGotoxy(0, y_nome + 2);
            printf("%*s", largura_tela, " ");
        }

        int x_input = (largura_tela - 30) / 2;
        screenGotoxy(x_input, y_nome + 1);
        printf("------------------------------");
        screenGotoxy(x_input, y_nome + 1);
        fgets(nome_jogador, 50, stdin);
        nome_jogador[strcspn(nome_jogador, "\n")] = '\0';

        if (!nome_valido(nome_jogador)) {
            screenSetColor(RED, BLACK);
            int x_erro = (largura_tela - 23) / 2;
            screenGotoxy(x_erro, y_nome + 3);
            printf("Nome inválido. Tente novamente.");
        }

        tentativa = 1;
        screenSetColor(WHITE, BLACK);
    } while (!nome_valido(nome_jogador));

    int x_bemvindo = (largura_tela - (37 + strlen(nome_jogador))) / 2;
    screenGotoxy(x_bemvindo, y_nome + 4);
    printf("Bem-vinde, %s! Pressione ENTER para começar!", nome_jogador);
    getchar();
}
