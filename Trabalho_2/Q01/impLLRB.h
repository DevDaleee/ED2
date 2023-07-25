#include <stdio.h>
#include <stdlib.h>

typedef struct arb ArvRN;

void rEsquerda(ArvRN **RaizArv);
void rDireita(ArvRN **RaizArv);
void trocaCor(ArvRN **RaizArv);
void balancearLLRB(ArvRN **RaizArv);
char verificaCor(ArvRN *RaizArv);
void EntradasDados(ArvRN **RaizArv, char *valor, int repetidas);
void inserir(ArvRN **RaizArv, char *valor, int repetidas);
void ImprimeArvoreInOrdemLLRB(ArvRN *RaizArv);