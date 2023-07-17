#include <stdio.h>
#include <stdlib.h>

typedef struct arb {
    int info;
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

ArvRN* EntradasDados(ArvRN **RaizArv, int valor) {
    if (*RaizArv == NULL) {
        ArvRN *newNode = (ArvRN*)malloc(sizeof(ArvRN));
        if (newNode != NULL) {
            newNode->info = valor;
            newNode->cor = 'R';
            newNode->dir = NULL;
            newNode->esq = NULL;
        } else {
            printf("Erro de alocacao de memoria!\n");
            exit(1);
        }
        return newNode;
    }

    if (valor == (*RaizArv)->info) {
        printf("Valor ja inserido!\n");
        exit(1);
    } else if (valor < (*RaizArv)->info) {
        (*RaizArv)->esq = EntradasDados(&(*RaizArv)->esq, valor);
    } else {
        (*RaizArv)->dir = EntradasDados(&(*RaizArv)->dir, valor);
    }
    balancearLLRB(&(*RaizArv));
    return (*RaizArv);
}

ArvRN* inserir(ArvRN **RaizArv, int valor) {
    *RaizArv = EntradasDados(RaizArv, valor);
    if (*RaizArv != NULL) {
        (*RaizArv)->cor = 'B';
    }
    return *RaizArv;
}

void ImprimeArvoreInOrdemLLRB(ArvRN *RaizArv) {
    if (RaizArv != NULL) {
        ImprimeArvoreInOrdemLLRB(RaizArv->esq);
        printf("%d ", RaizArv->info);
        printf("%c\n", RaizArv->cor);
        ImprimeArvoreInOrdemLLRB(RaizArv->dir);
    }
}