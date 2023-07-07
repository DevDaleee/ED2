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

ArvRN* EntradasDados(ArvRN **RaizArv, int valor, int *resp) {
    if (*RaizArv == NULL) {
        ArvRN *newNode = (ArvRN*)malloc(sizeof(ArvRN));
        if (newNode != NULL) {
            newNode->info = valor;
            newNode->cor = 'R';
            newNode->dir = NULL;
            newNode->esq = NULL;
            *resp = 1;
        } else {
            *resp = 0;
        }
        return newNode;
    }

    if (valor == (*RaizArv)->info) {
        *resp = 0; // Valor Duplicado
    } else if (valor < (*RaizArv)->info) {
        (*RaizArv)->esq = EntradasDados(&(*RaizArv)->esq, valor, resp);
    } else {
        (*RaizArv)->dir = EntradasDados(&(*RaizArv)->dir, valor, resp);
    }
    balancearLLRB(&(*RaizArv));
    return (*RaizArv);
}

ArvRN* inserir(ArvRN **RaizArv, int valor) {
    int resp = 0;
    *RaizArv = EntradasDados(RaizArv, valor, &resp);
    if (*RaizArv != NULL) {
        (*RaizArv)->cor = 'B';
    }
    return *RaizArv;
}

ArvRN* removerLLRB(ArvRN **RaizArv, int valor) {
    if (*RaizArv == NULL) {
        return NULL;
    }
    if (valor < (*RaizArv)->info) {
        if ((*RaizArv)->esq != NULL && (*RaizArv)->esq->cor == 'B' && (*RaizArv)->esq->esq != NULL && (*RaizArv)->esq->esq->cor == 'B') {
            rDireita(RaizArv);
        }
        (*RaizArv)->esq = removerLLRB(&(*RaizArv)->esq, valor);
    } else {
        if ((*RaizArv)->esq != NULL && (*RaizArv)->esq->cor == 'R') {
            rDireita(RaizArv);
        }
        if ((*RaizArv)->info == valor && (*RaizArv)->dir == NULL) {
            free(*RaizArv);
            return NULL;
        }
        if ((*RaizArv)->dir != NULL && (*RaizArv)->dir->cor == 'B' && (*RaizArv)->dir->esq != NULL && (*RaizArv)->dir->esq->cor == 'B') {
            rEsquerda(&(*RaizArv)->dir);
            if ((*RaizArv)->dir != NULL && (*RaizArv)->dir->dir != NULL && (*RaizArv)->dir->dir->cor == 'R') {
                rEsquerda(RaizArv);
            }
        }
        if ((*RaizArv)->info == valor) {
            ArvRN *aux = (*RaizArv)->dir;
            while (aux->esq != NULL) {
                aux = aux->esq;
            }
            (*RaizArv)->info = aux->info;
            (*RaizArv)->dir = removerLLRB(&(*RaizArv)->dir, (*RaizArv)->info);
        } else {
            (*RaizArv)->dir = removerLLRB(&(*RaizArv)->dir, valor);
        }
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