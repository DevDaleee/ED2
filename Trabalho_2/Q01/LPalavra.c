#include <stdio.h>
#include <stdlib.h>
#include "impLPalavra.h"

struct RLinhas {
    int Linha;
    rLinhas *prox;
};

void InserirLista(rLinhas **NoListaLinhas, int NumLinha) {
    if ((*NoListaLinhas) == NULL) {
        (*NoListaLinhas) = CriaNoLinha(NumLinha);
        (*NoListaLinhas)->prox = NULL;
    }
    else {
        InserirLista(&((*NoListaLinhas)->prox), NumLinha);
    }
}

rLinhas* CriaLista(int NumLinha) {
    rLinhas* NovoNo = (rLinhas*) malloc(sizeof(rLinhas));
    NovoNo->Linha = NumLinha;
    NovoNo->prox = NULL;
}

void ImprimirLista(rLinhas *NoListaLinhas) {
    if (NoListaLinhas != NULL) {
        printf("%d ", NoListaLinhas->Linha);
        ImprimirLista(NoListaLinhas->prox);
    }
}