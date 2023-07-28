#include <stdio.h>
#include <stdlib.h>
#include "impLista.h"

struct _Linhas {
    int NumLinha;
    Linhas *Prox;
};

void InsereNoLinha(Linhas **NoListaLinhas, int NumLinha) {
    if ((*NoListaLinhas) == NULL) {
        (*NoListaLinhas) = CriaNoLinha(NumLinha);
        (*NoListaLinhas)->Prox = NULL;
    }
    else {
        InsereNoLinha(&((*NoListaLinhas)->Prox), NumLinha);
    }
}

Linhas* CriaNoLinha(int NumLinha) {
    Linhas* NovoNo = (Linhas*) malloc(sizeof(Linhas));
    NovoNo->NumLinha = NumLinha;
    NovoNo->Prox = NULL;
}

void ImprimeListaLinhas(Linhas *NoListaLinhas) {
    if (NoListaLinhas != NULL) {
        printf("%d ", NoListaLinhas->NumLinha);
        ImprimeListaLinhas(NoListaLinhas->Prox);
    }
}