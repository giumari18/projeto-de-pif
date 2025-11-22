#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "ui.h"
#include "perfil.h"

#define ARQUIVO_RANKING "ranking.csv"
#define ARQUIVO_RECEITAS "recipes.csv" 
#define MAX_LINHA 4096

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

int menu_selecao_fase() {
    int escolha = -1;
    int total_receitas = 0;
    char buffer_input[10];
    char linha[MAX_LINHA];

    // Loop para manter o usuário na tela até escolher certo
    while (1) {
        screenClear();
        pintar_fundo(150, 45, BLACK);

        int y = 3;
        centralizar_texto("====================================================", y++);
        centralizar_texto("               LIVRO DE RECEITAS                    ", y++);
        centralizar_texto("====================================================", y++);
        y += 2;

        // 1. Ler o arquivo para listar as opções
        FILE *arquivo = fopen(ARQUIVO_RECEITAS, "r");
        if (!arquivo) {
            screenSetColor(RED, BLACK);
            centralizar_texto("Erro: Nao foi possivel abrir recipes.csv", y);
            getchar();
            return -1; // Retorna erro
        }

        total_receitas = 0;
        screenSetColor(YELLOW, BLACK); // Destaque para as opções
        
        while (fgets(linha, sizeof(linha), arquivo)) {
            // Remove o \n
            linha[strcspn(linha, "\n")] = 0;
            if (strlen(linha) == 0) continue;

            // Pega apenas o primeiro item (Nome da Receita)
            char *nome = strtok(linha, ",");
            if (nome) {
                char item_menu[100];
                sprintf(item_menu, "%d. %s", total_receitas + 1, nome);
                centralizar_texto(item_menu, y++);
                total_receitas++;
            }
        }
        fclose(arquivo);
        screenSetColor(WHITE, BLACK);

        if (total_receitas == 0) {
            centralizar_texto("Nenhuma receita encontrada no livro.", y);
            getchar();
            return -1;
        }

        // 2. Área de Input
        y += 2;
        centralizar_texto("Digite o numero da receita:", y++);
        
        // Desenha a linha de input
        int largura = 80;
        int x_input = (largura - 10) / 2;
        screenGotoxy(x_input, y);
        printf("__________");
        screenGotoxy(x_input, y);

        // Lê a escolha
        screenSetColor(LIGHTGRAY, BLACK);
        fgets(buffer_input, 10, stdin);
        screenSetColor(WHITE, BLACK);

        // Converte para número
        escolha = atoi(buffer_input);

        // Validação
        if (escolha > 0 && escolha <= total_receitas) {
            // Feedback visual de sucesso
            screenSetColor(GREEN, BLACK);
            centralizar_texto("Carregando ingredientes...", y + 2);
            getchar(); // Pequena pausa
            break; // Sai do loop while
        } else {
            // Feedback de erro
            screenSetColor(RED, BLACK);
            centralizar_texto("Opcao invalida! Tente novamente.", y + 2);
            screenSetColor(WHITE, BLACK);
            getchar(); // Espera o usuário ler o erro antes de limpar a tela
        }
    }

    // Retorna o índice (base 0) para o array/função de carga
    return escolha - 1; 
}