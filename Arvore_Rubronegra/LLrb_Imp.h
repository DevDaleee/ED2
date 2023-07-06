#include <stdio.h>
#include <stdlib.h>

typedef struct arb ArvRN;

void rEsquerda(ArvRN **RaizArv);
void rDireita(ArvRN **RaizArv);
void trocaCor(ArvRN **RaizArv);
void balancear(ArvRN **RaizArv);

ArvRN* EntradasDados(ArvRN **RaizArv, int valor, int *resp);
ArvRN* inserir(ArvRN **RaizArv, int valor);
ArvRN* remover(ArvRN **RaizArv, int valor);

void ImprimeArvore(ArvRN *RaizArv);