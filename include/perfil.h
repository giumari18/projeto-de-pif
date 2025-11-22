#ifndef PERFIL_H  
#define PERFIL_H  

typedef struct {
    char nome[50];
    int xp;
    char badge[30];
} Player;

void carregarArquivo(char *inputNome, Player *p);


char *toLower(char *c);

#endif
