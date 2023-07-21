#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct arb {
    char info[100];
    struct arb *esq;
    struct arb *dir;
    char cor;
} ArvRN;

void rEsquerda(ArvRN **RaizArv) {
    ArvRN *aux = (*RaizArv)->dir;
    (*RaizArv)->dir = aux->esq;
    aux->esq = (*RaizArv);
    aux->cor = (*RaizArv)->cor;
    (*RaizArv)->cor = 'R';
    (*RaizArv) = aux;
}

void rDireita(ArvRN **RaizArv) {
    ArvRN *aux = (*RaizArv)->esq;
    (*RaizArv)->esq = aux->dir;
    aux->dir = (*RaizArv);
    aux->cor = (*RaizArv)->cor;
    (*RaizArv)->cor = 'R';
    (*RaizArv) = aux;
}

void trocaCor(ArvRN **RaizArv) {
    (*RaizArv)->cor = 'R';
    (*RaizArv)->esq->cor = 'B';
    (*RaizArv)->dir->cor = 'B';
}

void balancearLLRB(ArvRN **RaizArv) {
    if ((*RaizArv)->dir != NULL && (*RaizArv)->dir->cor == 'R') {
        rEsquerda(RaizArv);
    }
    if ((*RaizArv)->esq != NULL && (*RaizArv)->esq->cor == 'R' && (*RaizArv)->esq->esq != NULL && (*RaizArv)->esq->esq->cor == 'R') {
        rDireita(RaizArv);
    }
    if ((*RaizArv)->esq != NULL && (*RaizArv)->esq->cor == 'R' && (*RaizArv)->dir != NULL && (*RaizArv)->dir->cor == 'R') {
        trocaCor(RaizArv);
    }
}

ArvRN* EntradasDados(ArvRN **RaizArv, char *valor) {
    if (*RaizArv == NULL) {
        *RaizArv = (ArvRN*) malloc(sizeof (ArvRN));
        strcpy((*RaizArv)->info, valor);
        (*RaizArv)->esq = NULL;
        (*RaizArv)->dir = NULL;
        (*RaizArv)->cor = 'R';
    } else {
        if (strcmp(valor, (*RaizArv)->info) < 0) {
            (*RaizArv)->esq = EntradasDados(&(*RaizArv)->esq, valor);
        } else {
            (*RaizArv)->dir = EntradasDados(&(*RaizArv)->dir, valor);
        }
    }
    balancearLLRB(RaizArv);
    return *RaizArv;
}

ArvRN* inserir(ArvRN **RaizArv, char *valor) {
    *RaizArv = EntradasDados(RaizArv, valor);
    if (*RaizArv != NULL) {
        (*RaizArv)->cor = 'B';
    }

}

void ImprimeArvoreInOrdemLLRB(ArvRN *RaizArv) {
    if (RaizArv != NULL) {
        ImprimeArvoreInOrdemLLRB(RaizArv->esq);
        printf("%s ", RaizArv->info);
        printf("%c\n", RaizArv->cor);
        ImprimeArvoreInOrdemLLRB(RaizArv->dir);
    }
}