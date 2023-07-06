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

void balancear(ArvRN **RaizArv) {
    if ((*RaizArv)->dir != NULL && (*RaizArv)->dir->cor == 'R') {
        if ((*RaizArv)->dir->esq != NULL && (*RaizArv)->dir->esq->cor == 'R') {
            rDireita(&(*RaizArv)->dir);
        }
        rEsquerda(RaizArv);
    } else if ((*RaizArv)->esq != NULL && (*RaizArv)->esq->cor == 'R') {
        if ((*RaizArv)->esq->dir != NULL && (*RaizArv)->esq->dir->cor == 'R') {
            rEsquerda(&(*RaizArv)->esq);
        }
        rDireita(RaizArv);
    } else if ((*RaizArv)->esq != NULL && (*RaizArv)->esq->cor == 'R' && (*RaizArv)->dir != NULL && (*RaizArv)->dir->cor == 'R') {
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
    balancear(&(*RaizArv));
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

ArvRN* remover(ArvRN **RaizArv, int valor) {
    if (*RaizArv == NULL) {
        return NULL;
    }
    if ((*RaizArv)->info > valor) {
        (*RaizArv)->esq = remover(&(*RaizArv)->esq, valor);
    } else if ((*RaizArv)->info < valor) {
        (*RaizArv)->dir = remover(&(*RaizArv)->dir, valor);
    } else {
        if ((*RaizArv)->esq == NULL && (*RaizArv)->dir == NULL) {
            free(*RaizArv);
            *RaizArv = NULL;
        } else if ((*RaizArv)->esq == NULL) {
            ArvRN *aux = *RaizArv;
            *RaizArv = (*RaizArv)->dir;
            free(aux);
        } else if ((*RaizArv)->dir == NULL) {
            ArvRN *aux = *RaizArv;
            *RaizArv = (*RaizArv)->esq;
            free(aux);
        } else {
            ArvRN *aux = (*RaizArv)->esq;
            while (aux->dir != NULL) {
                aux = aux->dir;
            }
            (*RaizArv)->info = aux->info;
            aux->info = valor;
            (*RaizArv)->esq = remover(&(*RaizArv)->esq, valor);
        }
    }
    balancear(RaizArv);
    return *RaizArv;
}

void ImprimeArvore(ArvRN *RaizArv) {
    if (RaizArv != NULL) {
        printf("%d ", RaizArv->info);
        printf("%c \n", RaizArv->cor);
        ImprimeArvore(RaizArv->esq);
        ImprimeArvore(RaizArv->dir);
    }
}