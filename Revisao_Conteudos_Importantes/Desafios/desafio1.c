#include <stdio.h>
#include <stdlib.h>

struct arv {
    int info;
    struct arv *dir, *esq;
};

struct raiz {
    struct arv *raiz;
};

void atribui(struct raiz **raizavb, struct arv *node);

int main() {
    typedef struct arv arvB;
    typedef struct raiz raizA;

    raizA *raizAbb = (raizA*) malloc(sizeof(raizA));
    arvB *newNode = (arvB*) malloc(sizeof(arvB));

    atribui(&raizAbb, newNode);

    free(newNode);
    free(raizAbb);

    return 0;
}

void atribui(struct raiz **raizavb, struct arv *node) {
    (*raizavb)->raiz = node;

    (*raizavb)->raiz->info = 2;
    (*raizavb)->raiz->dir = NULL;
    (*raizavb)->raiz->esq = NULL;

    printf("%d\n", (*raizavb)->raiz->info);
}
