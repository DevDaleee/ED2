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

void RemoveNoLinha(Linhas **NoListaLinhas, int NumLinha) {
    if ((*NoListaLinhas) != NULL) {
        if ((*NoListaLinhas)->NumLinha == NumLinha) {
            Linhas* Temp = (*NoListaLinhas);
            (*NoListaLinhas) = (*NoListaLinhas)->Prox;
            free(Temp);
        }
        else {
            RemoveNoLinha(&((*NoListaLinhas)->Prox), NumLinha);
        }
    }
}

void LiberaListaLinhas(Linhas **NoListaLinhas);

void ImprimeListaLinhas(Linhas *NoListaLinhas) {
    if (NoListaLinhas != NULL) {
        printf("%d ", NoListaLinhas->NumLinha);
        ImprimeListaLinhas(NoListaLinhas->Prox);
    }
}