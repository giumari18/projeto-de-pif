#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "perfil.h"
#include "ui.h"

#define FRAME_RATE_MS 50

#define STATE_SELECTING 0
#define STATE_ANSWERED  1

void drawChocolateCake(int x, int y, int state, int chosen, int correct);
void drawQuiz(const char *question, const char *options[], int numOptions, int selected, int state, int chosen, int correct);
void handleInput(int *selected, int *state, int *chosen, int *running, int numOptions);

int main() {
    Player player;

    keyboardInit();
    screenInit(1);
    timerInit(FRAME_RATE_MS);

    tela_inicial();
    historia(&player);

    const char *question = "Qual ingrediente essencial falta para um bolo de chocolate perfeito?";
    
    const char *quizOptions[] = {
        "A. Fermento em po",
        "B. Molho de tomate",
        "C. Pepino em conserva",
        "D. Picles picados"
    };
    int numOptions = 4;
    int correctOption = 0;

    int selectedOption = 0;
    int quizState = STATE_SELECTING;
    int chosenAnswer = -1;
    int isRunning = 1;

    while (isRunning) {
        handleInput(&selectedOption, &quizState, &chosenAnswer, &isRunning, numOptions);

        drawQuiz(question, quizOptions, numOptions, selectedOption, quizState, chosenAnswer, correctOption);

        while (!timerTimeOver()) {
            usleep(1000);
        }
    }

    keyboardDestroy();
    screenDestroy();

    return 0;
}

void drawChocolateCake(int x, int y, int state, int chosen, int correct) {
    screenSetColor(BROWN, BLACK);

    screenGotoxy(x + 2, y); printf(" _.-'-._ ");
    screenGotoxy(x + 1, y + 1); printf("/       \\");
    screenGotoxy(x, y + 2); printf("|  _   _  |");
    screenGotoxy(x, y + 3); printf("| | | | | |");
    screenGotoxy(x, y + 4); printf("| | | | | |");
    screenGotoxy(x, y + 5); printf("|  `---`  |");
    screenGotoxy(x + 1, y + 6); printf("\\_______/");

    screenGotoxy(x + 1, y + 1);
    if (state == STATE_ANSWERED && chosen == correct) {
        screenSetColor(LIGHTGREEN, BLACK);
    } else if (state == STATE_ANSWERED && chosen != correct) {
        screenSetColor(LIGHTRED, BLACK);
    } else {
        screenSetColor(WHITE, BLACK);
    }
    printf(" ~~~~~~~ ");

    if (state == STATE_ANSWERED && chosen == correct) {
        screenSetColor(RED, BLACK);
        screenGotoxy(x + 5, y + 1);
        printf("o");
    }
    
    screenSetColor(WHITE, BLACK);
}

void drawQuiz(const char *question, const char *options[], int numOptions, int selected, int state, int chosen, int correct) {
    int cakeX = (MAXX - MINX) / 2 - 5 + MINX;
    int cakeY = MINY + 2;
    drawChocolateCake(cakeX, cakeY, state, chosen, correct);

    int qLen = strlen(question);
    int qX = (MAXX - MINX) / 2 - qLen / 2 + MINX;
    int qY = cakeY + 8;
    
    screenGotoxy(qX, qY);
    screenSetColor(WHITE, BLACK);
    printf("%s", question);

    for (int i = 0; i < numOptions; i++) {
        int optLen = strlen(options[i]);
        int optX = (MAXX - MINX) / 2 - optLen / 2 + MINX;
        int optY = qY + 2 + i;

        screenGotoxy(optX - 3, optY);

        if (state == STATE_SELECTING) {
            if (i == selected) {
                screenSetColor(BLACK, WHITE);
                printf(" > %s < ", options[i]);
            } else {
                screenSetColor(WHITE, BLACK);
                printf("   %s   ", options[i]);
            }
        }
        else if (state == STATE_ANSWERED) {
            if (i == correct) {
                screenSetColor(LIGHTGREEN, BLACK);
                printf(" [ %s ] ", options[i]);
            }
            else if (i == chosen) {
                screenSetColor(LIGHTRED, BLACK);
                printf(" [ %s ] ", options[i]);
            }
            else {
                screenSetColor(GRAY, BLACK);
                printf("   %s   ", options[i]);
            }
        }
    }

    const char *help;
    if (state == STATE_SELECTING) {
        help = "Use 'w'/'s' para navegar e 'Enter' para confirmar.";
    } else {
        help = "Pressione 'q' para sair ou 'r' para tentar novamente!";
    }

    int helpLen = strlen(help);
    screenGotoxy((MAXX - MINX) / 2 - helpLen / 2 + MINX, MAXY - 2);
    screenSetColor(LIGHTGRAY, BLACK);
    printf("%s", help);

    screenHomeCursor();
}

void handleInput(int *selected, int *state, int *chosen, int *running, int numOptions) {
    if (!keyhit()) {
        return;
    }

    int ch = readch();

    if (*state == STATE_SELECTING) {
        switch (ch) {
            case 'w':
            case 'W':
                *selected = (*selected - 1 + numOptions) % numOptions;
                break;
            case 's':
            case 'S':
                *selected = (*selected + 1) % numOptions;
                break;
            case 10:
                *state = STATE_ANSWERED;
                *chosen = *selected;
                break;
            case 'q':
            case 'Q':
                *running = 0;
                break;
        }
    }
    else if (*state == STATE_ANSWERED) {
        if (ch == 'q' || ch == 'Q') {
            *running = 0;
        } else if (ch == 'r' || ch == 'R') {
            *state = STATE_SELECTING;
            *selected = 0;
            *chosen = -1;
            screenInit(1);
        }
    }
}