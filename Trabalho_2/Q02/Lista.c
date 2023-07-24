#include <stdio.h>
#include <stdlib.h>
#include "impLista.h"

struct Palavras {
    int NumLinha;
    LPalavras *Prox;
};

void InsereNoLinha(LPalavras **NoListaLinhas, int NumLinha) {
    if ((*NoListaLinhas) == NULL) {
        (*NoListaLinhas) = CriaNoLinha(NumLinha);
        (*NoListaLinhas)->Prox = NULL;
    }
    else {
        InsereNoLinha(&((*NoListaLinhas)->Prox), NumLinha);
    }
}

LPalavras* CriaNoLinha(int NumLinha) {
    LPalavras* NovoNo = (LPalavras*) malloc(sizeof(LPalavras));
    NovoNo->NumLinha = NumLinha;
    NovoNo->Prox = NULL;
}

void RemoveNoLinha(LPalavras **NoListaLinhas, int NumLinha) {
    if ((*NoListaLinhas) != NULL) {
        if ((*NoListaLinhas)->NumLinha == NumLinha) {
            LPalavras* Temp = (*NoListaLinhas);
            (*NoListaLinhas) = (*NoListaLinhas)->Prox;
            free(Temp);
        }
        else {
            RemoveNoLinha(&((*NoListaLinhas)->Prox), NumLinha);
        }
    }
}

void LiberaListaLinhas(LPalavras **NoListaLinhas);

void ImprimeListaLinhas(LPalavras *NoListaLinhas) {
    if (NoListaLinhas != NULL) {
        printf("%d ", NoListaLinhas->NumLinha);
        ImprimeListaLinhas(NoListaLinhas->Prox);
    }
}