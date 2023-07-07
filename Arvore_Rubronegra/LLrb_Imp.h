#include <stdio.h>
#include <stdlib.h>

typedef struct arb ArvRN;

void rEsquerda(ArvRN **RaizArv);
void rDireita(ArvRN **RaizArv);
void trocaCor(ArvRN **RaizArv);
void balancearLLRB(ArvRN **RaizArv);

ArvRN* EntradasDados(ArvRN **RaizArv, int valor, int *resp);
ArvRN* inserir(ArvRN **RaizArv, int valor);
ArvRN* removerLLRB(ArvRN **RaizArv, int valor);

void ImprimeArvoreInOrdemLLRB(ArvRN *RaizArv);