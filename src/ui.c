#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include "screen.h"
#include "keyboard.h"
#include "ui.h"
#include "perfil.h"
#include "xp.h"
#include "receitas.h"
#include "avaliacao.h"

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
        "                      ███ ░███                                                                                                                      ",
        "                     ░░██████                                                                                                                       ",
        "                      ░░░░░░                                                                                                                        ",
        "",
        "ㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤㅤPressione ENTER para iniciar ou ESC para sair"
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

        screenGotoxy(x_input, y_nome + 2);
        screenSetColor(LIGHTGRAY, BLACK);
        
        fgets(p->nome, 50, stdin);
        
        screenSetColor(WHITE, BLACK);

        p->nome[strcspn(p->nome, "\n")] = '\0';

        if (!nome_valido(p->nome)) {
            screenSetColor(RED, BLACK);
            centralizar_texto("Nome inválido. Tente novamente.", y_nome + 4);
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
    centralizar_texto("                  LOGICA A LA CARTE                 ", y++);
    centralizar_texto("====================================================", y++);

    screenSetColor(LIGHTGRAY, BLACK);
    y++;

    centralizar_texto("Um dia, o professor Diego simplesmente desistiu.", y++);
    centralizar_texto("Largou a vida de tecnologia, saiu da CESAR School,", y++);
    centralizar_texto("e decidiu seguir sua verdadeira vocação: a gastronomia.", y++);
    centralizar_texto("Diego possui extrema habilidade culinária, mas organizou", y++);
    centralizar_texto("seu livro de receitas de maneira um tanto peculiar...", y++);
    centralizar_texto("utilizando premissas e relações lógico-matemáticas para", y++);
    centralizar_texto("estruturar cada ingrediente e etapa do preparo.", y++);
    centralizar_texto(" ", y++);
    centralizar_texto("E cabe a VOCÊ ajudá-lo nessa nova jornada.", y++);

    screenSetColor(GREEN, BLACK);
    centralizar_texto("Pronto para começar?", y + 2);
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

int menuSelecaoFase() {
    int escolha = -1;
    int total_receitas = 0;
    char buffer_input[10];
    char linha[MAX_LINHA];

    // Loop de mostrar na tela as opções de receitas
    while (1) {
        screenClear();
        pintar_fundo(150, 45, BLACK);

        int y = 3;
        centralizar_texto("====================================================", y++);
        centralizar_texto("                  LIVRO DE RECEITAS                 ", y++);
        centralizar_texto("====================================================", y++);
        y += 2;

        FILE *arquivo = fopen(ARQUIVO_RECEITAS, "r");

        total_receitas = 0;

        screenSetColor(YELLOW, BLACK);
        
        while (fgets(linha, sizeof(linha), arquivo)) {
            // Remove o \n do buffer e ignora linhas vazias com essas duas linhas abaixo respectivamente
            linha[strcspn(linha, "\n")] = 0;
            if (strlen(linha) == 0) continue;

            // Pega apenas o primeiro item (Nome da Receita) no arquivo CSV
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

        y += 2;
        centralizar_texto("Digite o número da receita:", y++);
        
        int largura = 80;
        int x_input = (largura - 10) / 2;
        screenGotoxy(x_input, y);
        screenGotoxy(x_input, y);

        screenSetColor(LIGHTGRAY, BLACK);
        fgets(buffer_input, 10, stdin);
        screenSetColor(WHITE, BLACK);

        escolha = atoi(buffer_input);

        if (escolha > 0 && escolha <= total_receitas) {
            screenSetColor(GREEN, BLACK);
            centralizar_texto("Carregando ingredientes...", y + 2);
            getchar(); 
            break; 
        } else {
            screenSetColor(RED, BLACK);
            centralizar_texto("Opção inválida! Tente novamente.", y + 2);
            screenSetColor(WHITE, BLACK);
            getchar();
        }
    }
    return escolha - 1; 
}

int rodarQuestaoIngrediente(Ingrediente *ing, int indice, int total) {
    int selecionado = 0; // 0=A, 1=B, 2=C, 3=D
    int rodando = 1;

    while (rodando) {

        screenClear();
        pintar_fundo(150, 45, BLACK);

        char titulo[100];
        sprintf(titulo, "INGREDIENTE %d / %d", indice, total);
        
        screenSetColor(CYAN, BLACK);
        centralizar_texto("========================================", 2);
        centralizar_texto(titulo, 3);
        centralizar_texto("========================================", 4);

        screenSetColor(YELLOW, BLACK);
        centralizar_texto("--- DICAS ---", 7);
        
        screenSetColor(WHITE, BLACK);
        for (int i = 0; i < 4; i++) {
            if (strlen(ing->premissas[i]) > 0) {
                screenGotoxy(30, 9 + i); 
                printf("- %s", ing->premissas[i]);
            }
        }

        screenSetColor(GREEN, BLACK);
        centralizar_texto("--- QUAL A ALTERNATIVA? ---", 15);

        for (int i = 0; i < 4; i++) {
            int y_pos = 18 + (i * 2); 
            int x_pos = 30; 

            screenGotoxy(x_pos, y_pos);

            //Se o i for o que está selecionado, grifa ele em branco se não, normal
            if (i == selecionado) {
                screenSetColor(BLACK, WHITE); 
                printf(" > %c) %s < ", 'A' + i, ing->alternativas[i]);
            } else {
                screenSetColor(WHITE, BLACK);
                printf("   %c) %s   ", 'A' + i, ing->alternativas[i]);
            }
        }

        screenSetColor(GRAY, BLACK);
        centralizar_texto("Use W/S para navegar e ENTER para confirmar", 30);

        //USUARIO SELECIONAR UMA OPCAO
        if (keyhit()) {
            int ch = readch();

            if (ch == 'w' || ch == 'W') {
                selecionado--;
                if (selecionado < 0) selecionado = 3; 
            }
            else if (ch == 's' || ch == 'S') {
                selecionado++;
                if (selecionado > 3) selecionado = 0; 
            }
            else if (ch == 10 || ch == 13) { 
                rodando = 0; 
            }
        }

        // Pequena pausa para não fritar a CPU
        usleep(50000); // 50ms
    }

    return selecionado; // Retorna 0, 1, 2 ou 3 para a opção final quando o user clicou enter
}

void mostrarTelaAcerto(char *resposta, int xpGanho) {
    screenClear();
    pintar_fundo(150, 45, BLACK);
    
    screenSetColor(GREEN, BLACK);
    centralizar_texto("VAMOS ARRASANDO!", 15);
    
    char msg[100];
    sprintf(msg, "O ingrediente era: %s", resposta);
    screenSetColor(WHITE, BLACK);
    centralizar_texto(msg, 17);

    sprintf(msg, "+%d XP", xpGanho);
    screenSetColor(YELLOW, BLACK);
    centralizar_texto(msg, 19);

    screenSetColor(WHITE, BLACK);
    getchar(); // Espera um Enter 
}

void mostrarTelaErro(char *escolha, char *correta) {
    screenClear();
    pintar_fundo(150, 45, BLACK);
    
    screenSetColor(RED, BLACK);
    centralizar_texto("VIXY, TÁ ERRADO...", 15);
    
    char msg[100];
    sprintf(msg, "Você escolheu: %s", escolha);
    screenSetColor(GRAY, BLACK);
    centralizar_texto(msg, 17);

    sprintf(msg, "A resposta certa era: %s", correta);
    screenSetColor(WHITE, BLACK);
    centralizar_texto(msg, 19);

    getchar(); // Espera um enter
}

void mostrarFimFase(char *nomeReceita) {
    screenClear();
    pintar_fundo(150, 45, BLACK);
    screenSetColor(CYAN, BLACK);
    centralizar_texto("RECEITA CONCLUÍDA!", 15);
    centralizar_texto(nomeReceita, 17);
    screenSetColor(WHITE, BLACK);
    centralizar_texto("Pressione ENTER para voltar ao menu", 20);
    getchar();
}



void jogarFase(Receita *r, Player *p) {
    int xp_por_acerto = 50;
    int qntAcertos = 0;

    for (int i = 0; i < r->quantidadeIngredientes; i++) {
        
        Ingrediente *ingAtual = &r->ingredientes[i];

        int indiceEscolhido = rodarQuestaoIngrediente(ingAtual, i + 1, r->quantidadeIngredientes);

        char *textoEscolhido = ingAtual->alternativas[indiceEscolhido];

        if (strcmp(textoEscolhido, ingAtual->alternativaCerta) == 0) {
            atualizarXP(xp_por_acerto, p);
            mostrarTelaAcerto(ingAtual->alternativaCerta, xp_por_acerto);
        } else {
            mostrarTelaErro(textoEscolhido, ingAtual->alternativaCerta);            
        }
    }

    // Fim da receita (aprimorar esse fim de fase pra mostrar estrelas obtidas ou algo assim)
    mostrarFimFase(r->nome);
}