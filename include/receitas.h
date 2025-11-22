
typedef struct{

    char nome[50];
    char premissas[10][100];
    char alternativas[4][100];
    char alternativaCerta[100];
    int quantidadePremissas;

} Ingrediente;


typedef struct{

    char nome[50];
    Ingrediente ingredientes[10];

} Receita;


void carregarReceitas(Receita receitas[], int *linhaReceita);


