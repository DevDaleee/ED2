#include <stdio.h>
#include <stdlib.h>

typedef struct arb ArvRN;

void rEsquerda(ArvRN **RaizArv);
void rDireita(ArvRN **RaizArv);
void trocaCor(ArvRN **RaizArv);
void balancearLLRB(ArvRN **RaizArv);

ArvRN* EntradasDados(ArvRN **RaizArv, char *valor);
ArvRN* inserir(ArvRN **RaizArv, char *valor);

void ImprimeArvoreInOrdemLLRB(ArvRN *RaizArv);