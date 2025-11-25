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
#include "ranking.h"

#define ARQUIVO_PROGRESSO "progresso.csv"
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
        "ㅤㅤㅤ █████                          ███                                         ", 
        "ㅤㅤㅤ▒▒███                          ▒▒▒                                          ", 
        "ㅤㅤㅤ ▒███         ██████   ███████ ████   ██████   ██████       ██████          ", 
        "ㅤㅤㅤ ▒███        ███▒▒███ ███▒▒███▒▒███  ███▒▒███ ▒▒▒▒▒███     ▒▒▒▒▒███         ", 
        "ㅤㅤㅤ ▒███       ▒███ ▒███▒███ ▒███ ▒███ ▒███ ▒▒▒   ███████      ███████         ", 
        "ㅤㅤㅤ ▒███      █▒███ ▒███▒███ ▒███ ▒███ ▒███  ███ ███▒▒███     ███▒▒███         ", 
        "ㅤㅤㅤ ███████████▒▒██████ ▒▒███████ █████▒▒██████ ▒▒████████   ▒▒████████        ", 
        "ㅤㅤㅤ▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒   ▒▒▒▒▒███▒▒▒▒▒  ▒▒▒▒▒▒   ▒▒▒▒▒▒▒▒     ▒▒▒▒▒▒▒▒         ", 
        "ㅤㅤㅤ                      ███ ▒███                                              ", 
        "ㅤㅤㅤ                     ▒▒██████                                               ", 
        "ㅤㅤㅤ                      ▒▒▒▒▒▒                                                ", 
        "ㅤㅤㅤ █████                      █████████                       █████           ", 
        "ㅤㅤㅤ▒▒███                      ███▒▒▒▒▒███                     ▒▒███            ", 
        "ㅤㅤㅤ ▒███         ██████      ███     ▒▒▒   ██████   ████████  ███████    ██████", 
        "ㅤㅤㅤ ▒███        ▒▒▒▒▒███    ▒███          ▒▒▒▒▒███ ▒▒███▒▒███▒▒▒███▒    ███▒▒███",
        "ㅤㅤㅤ ▒███         ███████    ▒███           ███████  ▒███ ▒▒▒   ▒███    ▒███████", 
        "ㅤㅤㅤ ▒███      █ ███▒▒███    ▒▒███     ███ ███▒▒███  ▒███       ▒███ ███▒███▒▒▒",  
        "ㅤㅤㅤ ███████████▒▒████████    ▒▒█████████ ▒▒████████ █████      ▒▒█████ ▒▒██████", 
        "ㅤㅤㅤㅤ▒▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒▒▒▒      ▒▒▒▒▒▒▒▒▒   ▒▒▒▒▒▒▒▒ ▒▒▒▒▒        ▒▒▒▒▒   ▒▒▒▒▒▒",
        "ㅤ",
        "ㅤ",
        "ㅤㅤㅤㅤPressione ENTER para iniciar ou ESC para sair"
    };

    screenClear();
    pintar_fundo(150, 45, BLACK);
    screenSetColor(WHITE, BLACK);

    int y = 3;
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

    int largura_caixa = 40;
    int x_caixa = (largura - largura_caixa) / 2;
    
    screenSetColor(LIGHTGRAY, BLACK);
    
    screenGotoxy(x_caixa, y_nome + 2);
    printf("┌");
    for (int i = 0; i < largura_caixa - 2; i++) printf("─");
    printf("┐");
    
    screenGotoxy(x_caixa, y_nome + 3);
    printf("│");
    screenGotoxy(x_caixa + largura_caixa - 1, y_nome + 3);
    printf("│");
    
    screenGotoxy(x_caixa, y_nome + 4);
    printf("└");
    for (int i = 0; i < largura_caixa - 2; i++) printf("─");
    printf("┘");
    
    screenSetColor(LIGHTGRAY, BLACK);
    centralizar_texto("Pressione ENTER para confirmar", y_nome + 6);
    screenSetColor(WHITE, BLACK);

    do {
        if (tentativa) {
            screenGotoxy(0, y_nome + 8);
            printf("%*s", largura, " "); 
        }

        screenGotoxy(x_caixa + 1, y_nome + 3);
        printf("%*s", largura_caixa - 2, " ");
        
        screenGotoxy(x_caixa + 2, y_nome + 3);
        screenSetColor(WHITE, BLACK);
        
        fgets(p->nome, largura_caixa - 4, stdin);
        
        screenSetColor(WHITE, BLACK);

        p->nome[strcspn(p->nome, "\n")] = '\0';

        if (!nome_valido(p->nome)) {
            screenSetColor(RED, BLACK);
            centralizar_texto("Nome inválido. Tente novamente.", y_nome + 8);
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
    centralizar_texto("                  LÓGICA À LA CARTE                 ", y++);
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

    int nivel = calcularNivel(p->xp);

    char mensagem[120];

    sprintf(mensagem, "Bem-vinde, Chef %s! (Nível %d - XP: %d). ENTER para iniciar!", p->nome, nivel, p->xp);

    centralizar_texto(mensagem, 16);
    getchar();
}

void mostrarTelaRanking() {
    Player topJogadores[100]; 

    int total = buscarRanking(topJogadores, 100);

    screenClear();
    pintar_fundo(150, 45, BLACK);

    screenSetColor(CYAN, BLACK);
    const char *arte_titulo[] = {                             
    "█████▄  ▄████▄ ███  ██ ██ ▄█▀ ██ ███  ██  ▄████  ",              
    "██▄▄██▄ ██▄▄██ ██ ▀▄██ ████   ██ ██ ▀▄██ ██  ▄▄▄ ",
    "██   ██ ██  ██ ██   ██ ██ ▀█▄ ██ ██   ██  ▀███▀ "};                  
        
    screenSetColor(WHITE, BLACK);
    int linhas_titulo = sizeof(arte_titulo) / sizeof(arte_titulo[0]);
    int y_titulo = 1;
    
    int max_len_titulo = 0;
    for (int i = 0; i < linhas_titulo; i++) {
        int len = strlen(arte_titulo[i]);
        if (len > max_len_titulo) max_len_titulo = len;
    }
    
    int x_titulo = (80 - max_len_titulo) / 2;
    for (int i = 0; i < linhas_titulo; i++) {
        screenGotoxy(x_titulo, y_titulo + i);
        printf("%s", arte_titulo[i]);
    }
    
    int x_lista = 6;
    int y_lista = 6;
    int limite = (total > 10) ? 10 : total;

    for (int i = 0; i < limite; i++) {
        screenGotoxy(x_lista, y_lista + 3 + i); 
        
        if (i == 0) screenSetColor(YELLOW, BLACK);      
        else if (i == 1) screenSetColor(LIGHTGRAY, BLACK); 
        else if (i == 2) screenSetColor(BROWN, BLACK);  
        else screenSetColor(WHITE, BLACK);

        printf("#%-2d   %-18s %5d XP", i + 1, topJogadores[i].nome, topJogadores[i].xp);
    }

    if (total == 0) {
        screenSetColor(GRAY, BLACK);
        screenGotoxy(x_lista, y_lista + 3);
        printf("Nenhum chef registrado ainda.");
    }

    screenSetColor(WHITE, BLACK);
    const char *arte[] = {                             
        "            █████",              
        "        ████     ████",          
        "      █               █",       
        "      █               █",        
        "       ██           ██",         
        "        █████████████",          
        "       █ █   █    █ █",          
        "        ██          █",          
        "          ██      ██",        
        "          ██████████",          
        "        █     █  █   █",        
        "        █  █         █",         
        "          ██████████",          
        "          ████  ████",                                                                              
    };                  

    int linhas_arte = sizeof(arte) / sizeof(arte[0]);
    int x_arte = 45; 
    int y_arte = 6; 
    
    for (int i = 0; i < linhas_arte; i++) {
        screenGotoxy(x_arte, y_arte + i);
        printf("%s", arte[i]);
    }

    screenSetColor(GREEN, BLACK);
    centralizar_texto("Pressione ENTER para continuar", 22);
    
    getchar(); 
}

int buscar_estrelas(const char *nomeJogador, const char *nomeFase) {
    FILE *arquivo = fopen(ARQUIVO_PROGRESSO, "r");
    if (!arquivo) return 0;

    char linha[MAX_LINHA];
    int estrelas = 0;

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        
        char *csvNome = strtok(linha, ",");
        char *csvFase = strtok(NULL, ",");
        char *csvEstrelas = strtok(NULL, ",");

        if (csvNome && csvFase && csvEstrelas) {
            if (strcmp(csvNome, nomeJogador) == 0 && strcmp(csvFase, nomeFase) == 0) {
                estrelas = atoi(csvEstrelas);
                break;
            }
        }
    }
    fclose(arquivo);
    return estrelas;
}


void montar_string_estrelas(int qtd, char *buffer) {
    buffer[0] = '\0'; 
    for (int i = 0; i < 5; i++) {
        if (i < qtd) strcat(buffer, "★ ");
        else strcat(buffer, "☆ ");
    }
}

void desenhar_barra_xp(int xpAtual, int nivel) {
    float valorPorcentagem = 0.0;
    float meta = 0.0;
    
    switch(nivel){
        case 1: meta = 300.0; break;
        case 2: meta = 750.0; break;
        case 3: meta = 1250.0; break;
        case 4: meta = 1700.0; break;
        default: meta = 300.0;
    }

    if (meta > 0) {
        valorPorcentagem = (float)xpAtual / meta;
    }
    
    if (valorPorcentagem > 1.0) valorPorcentagem = 1.0;

  
    if(valorPorcentagem == 0){
        screenGotoxy(2, 1);
        screenSetColor(CYAN, BLACK);
        printf("Progresso do Nível: ░░░░░░░░░░░░░░░░░░░░");
    } else if(valorPorcentagem > 0 && valorPorcentagem <= 0.2){
        screenGotoxy(2, 1);
        screenSetColor(CYAN, BLACK);
        printf("Progresso do nivel: ████░░░░░░░░░░░░░░░░");
    } else if(valorPorcentagem > 0.2 && valorPorcentagem <= 0.4){
        screenGotoxy(2, 1);
        screenSetColor(CYAN, BLACK);
        printf("Progresso do nivel: ████████░░░░░░░░░░░░");
    } else if(valorPorcentagem > 0.4 && valorPorcentagem <= 0.6){
        screenGotoxy(2, 1);
        screenSetColor(CYAN, BLACK);
        printf("Progresso do nivel: ████████████░░░░░░░░");
    } else if(valorPorcentagem > 0.6 && valorPorcentagem <= 0.8){
        screenGotoxy(2, 1);
        screenSetColor(CYAN, BLACK);
        printf("Progresso do nivel: ████████████████░░░░");
    } else{
        screenGotoxy(2, 1);
        screenSetColor(CYAN, BLACK);
        printf("Progresso do nivel: ███████████████████░");
    }
}

const char* obter_titulo_chef(int nivel) {
    if (nivel == 1) return "Commis Chef";
    else if (nivel == 2) return "Chef de Partie";
    else if (nivel == 3) return "Sous Chef";
    else if (nivel == 4) return "Chef de Cuisine";
}

void desenhar_titulo_chef(Player *p) {
    int nivel = calcularNivel(p->xp);
    const char *titulo = obter_titulo_chef(nivel);
    
    char texto_completo[100];
    sprintf(texto_completo, "Nível do Chefe: %s", titulo);
    
    int largura_tela = 80;
    int tamanho_texto = strlen(texto_completo);
    int x_pos = largura_tela - tamanho_texto - 2;
    
    screenGotoxy(x_pos, 1);
    screenSetColor(YELLOW, BLACK);
    printf("%s", texto_completo);
}

int menuSelecaoFase(Player *p) {
    int escolha = -1;
    int total_receitas = 0;
    char buffer_input[10];
    char linha[MAX_LINHA];

    while (1) {
        screenClear();
        pintar_fundo(150, 45, BLACK);
        pintar_fundo(150, 45, BLACK);
        desenhar_barra_xp(p->xp, calcularNivel(p->xp));
        desenhar_titulo_chef(p);

        int y = 5;

    screenSetColor(WHITE, BLACK);
    centralizar_texto("                LIVRO DE RECEITAS DO DIEGO             ", y++);
    y++;
    y++;
    y++;

        screenSetColor(WHITE, BLACK);

        FILE *arquivo = fopen(ARQUIVO_RECEITAS, "r");
        
        

        total_receitas = 0;
        
        while (fgets(linha, sizeof(linha), arquivo)) {

            linha[strcspn(linha, "\n")] = 0;
            if (strlen(linha) == 0) continue;

            char *nome_receita = strtok(linha, ",");
            

            char *nivel_txt = strtok(NULL, ",");
            int nivel_receita = nivel_txt ? atoi(nivel_txt) : 1;
            
            if (nome_receita && nivel_receita <= calcularNivel(p->xp)) {

                int qtd_estrelas = buscar_estrelas(p->nome, nome_receita);

                char desenho_estrelas[30];
                montar_string_estrelas(qtd_estrelas, desenho_estrelas);

                char item_menu[150];
                
                if (qtd_estrelas > 0) screenSetColor(YELLOW, BLACK);
                else screenSetColor(WHITE, BLACK);

                sprintf(item_menu, "%d. %-60s  %s", total_receitas + 1, nome_receita, desenho_estrelas);
                
                screenGotoxy(2, y);  
                printf("%s", item_menu);
                y++;
                total_receitas++;
    }
}

        fclose(arquivo);
        screenSetColor(WHITE, BLACK);

        y += 2;
        centralizar_texto("Digite o número da receita:", y++);
        y++; 
       
        int largura = 80;
        int largura_caixa = 20;
        int x_caixa = (largura - largura_caixa) / 2;
        
        screenSetColor(LIGHTGRAY, BLACK);
        
        screenGotoxy(x_caixa, y);
        printf("┌");
        for (int i = 0; i < largura_caixa - 2; i++) printf("─");
        printf("┐");
        
        screenGotoxy(x_caixa, y + 1);
        printf("│");
        screenGotoxy(x_caixa + largura_caixa - 1, y + 1);
        printf("│");
        
        screenGotoxy(x_caixa, y + 2);
        printf("└");
        for (int i = 0; i < largura_caixa - 2; i++) printf("─");
        printf("┘");
        
        screenSetColor(LIGHTGRAY, BLACK);
        centralizar_texto("Pressione ENTER para confirmar", y + 4);
        
        screenGotoxy(x_caixa + 2, y + 1);
        screenSetColor(WHITE, BLACK);
        
        fgets(buffer_input, 10, stdin);
        screenSetColor(WHITE, BLACK);

        escolha = atoi(buffer_input);

        if (escolha > 0 && escolha <= total_receitas) {
            screenSetColor(GREEN, BLACK);
            centralizar_texto("Carregando ingredientes...", y + 6);
            fflush(stdout);
            usleep(2000000); 
            break; 
        } else {
            screenSetColor(RED, BLACK);
            centralizar_texto("Opção inválida! Tente novamente.", y + 6);
            screenSetColor(WHITE, BLACK);
            usleep(1500000); 
        }
    }
    return escolha - 1; 
}

int rodarQuestaoIngrediente(Ingrediente *ing, int indice, int total, const char *nomeReceita) {
    int selecionado = 0;
    int rodando = 1;
    int desenhar = 1; 

    screenClear();
    pintar_fundo(150, 45, BLACK);

    screenSetColor(WHITE, BLACK);

    // Título da receita
    screenSetColor(CYAN, BLACK);
    screenGotoxy(2, 1);
    printf("%s - INGREDIENTE %d / %d", nomeReceita, indice, total);

screenSetColor(WHITE, BLACK);
const char *arte[] = {                             
"           █████",              
"       ████     ████",          
"     █               █",       
"     █               █",        
"      ██           ██",         
"       █████████████",          
"      █ █   █    █ █",          
"       ██          █",          
"         ██      ██",           
"        █  ██   █ █",           
"       █  ████████ ███████",    
"        ███████████   ███",     
"         █████████"                                      
    };                  

    int x_arte = 50;
    int y_arte = 4;
    
    int linhas_arte = sizeof(arte) / sizeof(arte[0]);
    for (int i = 0; i < linhas_arte; i++) {
        screenGotoxy(x_arte, y_arte + i);
        printf("%s", arte[i]);
    }
    
    // Premissas mais em cima (começando na linha 5)
  screenSetColor(WHITE, BLACK);
    for (int i = 0; i < 5; i++) {
    // Adiciona um espaço entre a quarta (índice 3) e a quinta (índice 4)
    int linha = 4 + i;
    if (i == 4) linha++; // pule uma linha extra para a quinta premissa

    if (i == 4) {
        screenSetColor(RED, BLACK);   // quinta premissa em vermelho
    } else {
        screenSetColor(WHITE, BLACK); // demais em branco
    }

    screenGotoxy(2, linha);
    if (ing->premissas[i][0] != '\0') {
        printf("- %s", ing->premissas[i]);
    } else {
        printf("-");
    }
}


    // Pergunta
    screenSetColor(GREEN, BLACK);
    screenGotoxy(2, 10);
    printf("\nQual é o ingrediente?");

    fflush(stdout); 

    while (rodando) {
        
        if (desenhar) {
            for (int i = 0; i < 4; i++) {
                int y_pos = 13 + (i * 2);
                int x_pos = 2; 

                screenGotoxy(x_pos, y_pos);

                if (i == selecionado) {
                    screenSetColor(BLACK, WHITE); 
                    printf(" > %c) %s < ", 'A' + i, ing->alternativas[i]);
                } else {
                    screenSetColor(WHITE, BLACK);
                    printf("   %c) %s   ", 'A' + i, ing->alternativas[i]);
                }
            }
            
            // Instruções embaixo das alternativas (linha 23)
            screenSetColor(GRAY, BLACK);
            centralizar_texto("Use W/S para navegar e ENTER para confirmar", 21);
            
            screenSetColor(WHITE, BLACK); 
            fflush(stdout); 
            desenhar = 0; 
        }

        if (keyhit()) {
            int ch = readch();

            if (ch == 'w' || ch == 'W') {
                selecionado--;
                if (selecionado < 0) selecionado = 3;
                desenhar = 1;
            }
            else if (ch == 's' || ch == 'S') {
                selecionado++;
                if (selecionado > 3) selecionado = 0;
                desenhar = 1;
            }
            else if (ch == 10 || ch == 13) { 
                rodando = 0;
            }
        }

        usleep(50000); 
    }

    return selecionado;
}
void mostrarTelaAcerto(char *resposta, int xpGanho) {
    screenClear();
    pintar_fundo(150, 45, BLACK);
    
    screenSetColor(GREEN, BLACK);
    centralizar_texto("VAMOS ARRASANDO!", 6);
    
    char msg[100];
    sprintf(msg, "O ingrediente era: %s", resposta);
    screenSetColor(WHITE, BLACK);
    centralizar_texto(msg, 8);

    sprintf(msg, "+%d XP", xpGanho);
    screenSetColor(YELLOW, BLACK);
    centralizar_texto(msg, 10);

    screenSetColor(WHITE, BLACK);
    getchar(); 
}

void mostrarTelaErro(char *escolha, char *correta) {
    screenClear();
    pintar_fundo(150, 45, BLACK);
    
    screenSetColor(RED, BLACK);
    centralizar_texto("VIXY, TÁ ERRADO...", 6);
    
    char msg[100];
    sprintf(msg, "Você escolheu: %s", escolha);
    screenSetColor(GRAY, BLACK);
    centralizar_texto(msg, 8);

    sprintf(msg, "A resposta certa era: %s", correta);
    screenSetColor(WHITE, BLACK);
    centralizar_texto(msg, 10);

    getchar(); 
}

void mostrarFimFase(Player *p, char *nomeReceita, int quantidadeAcertos, int totalQuestoes) {
    screenClear();
    pintar_fundo(150, 45, BLACK);
    
    // Arte "FIM DE FASE!" no topo
    screenSetColor(CYAN, BLACK);
    const char *arte_titulo[] = {
        "      ██████ ██ ██▄  ▄██   ████▄  ██████   ██████ ▄████▄ ▄█████ ██████  ██",
        "      ██▄▄   ██ ██ ▀▀ ██   ██  ██ ██▄▄     ██▄▄   ██▄▄██ ▀▀▀▄▄▄ ██▄▄    ██",
        "      ██     ██ ██    ██   ████▀  ██▄▄▄▄   ██     ██  ██ █████▀ ██▄▄▄▄  ▄▄"
    };
    
    int linhas_titulo = sizeof(arte_titulo) / sizeof(arte_titulo[0]);
    int y_titulo = 1;
    
    int max_len_titulo = 0;
    for (int i = 0; i < linhas_titulo; i++) {
        int len = strlen(arte_titulo[i]);
        if (len > max_len_titulo) max_len_titulo = len;
    }
    
    int x_titulo = (80 - max_len_titulo) / 2;
    for (int i = 0; i < linhas_titulo; i++) {
        screenGotoxy(x_titulo, y_titulo + i);
        printf("%s", arte_titulo[i]);
    }
    
    // Sua avaliação
    screenSetColor(WHITE, BLACK);
    centralizar_texto("Sua avaliação:", 5);
    
    // Estrelas
    screenGotoxy(34, 7);
    definirEstrelas(p, nomeReceita, quantidadeAcertos, totalQuestoes);
    
    // Arte ASCII embaixo das estrelas
    screenSetColor(WHITE, BLACK);
    const char *arte[] = {                             
        "            █████",              
        "        ████     ████",          
        "      █               █",       
        "      █               █",        
        "       ██           ██",         
        "        █████████████",          
        "       █ █   █    █ █",          
        "        ██          █",          
        "          ██      ██",        
        "          ██████████",          
        "        █     █  █   █",        
        "        █  █         █",         
        "          ██████████",          
        "          ████  ████",                                                                              
    };                  

    int linhas_arte = sizeof(arte) / sizeof(arte[0]);
    int y_arte = 9;
    
    // Calcular a largura real (sem espaços no início)
    int x_base = 24; // Posição fixa centralizada
    
    for (int i = 0; i < linhas_arte; i++) {
        screenGotoxy(x_base, y_arte + i);
        printf("%s", arte[i]);
    }
    
    // Mensagem final
    int y_final = 24;
    screenSetColor(WHITE, BLACK);
    centralizar_texto("Pressione ENTER para voltar ao menu", y_final);
    
    fflush(stdout);
    getchar();
}

void jogarFase(Receita *r, Player *p) {
    int xp_por_acerto = 50;
    int qntAcertos = 0;

    for (int i = 0; i < r->quantidadeIngredientes; i++) {
        
        Ingrediente *ingAtual = &r->ingredientes[i];

        int indiceEscolhido = rodarQuestaoIngrediente(ingAtual, i + 1, r->quantidadeIngredientes, r->nome);

        char *textoEscolhido = ingAtual->alternativas[indiceEscolhido];

        if (strcmp(textoEscolhido, ingAtual->alternativaCerta) == 0) {
            atualizarXP(xp_por_acerto, p);
            qntAcertos++;
            mostrarTelaAcerto(ingAtual->alternativaCerta, xp_por_acerto);
        } else {
            mostrarTelaErro(textoEscolhido, ingAtual->alternativaCerta);            
        }
    }

    definirEstrelas(p, r->nome, qntAcertos, r->quantidadeIngredientes);
    mostrarFimFase(p, r->nome, qntAcertos, r->quantidadeIngredientes);
}
