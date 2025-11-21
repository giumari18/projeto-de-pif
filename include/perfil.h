#ifndef PERFIL_H  
#define PERFIL_H  

typedef struct {
    char nome[50];
    int xp;
} Player;

void carregarArquivo(char *inputNome, Player *p);

#endif