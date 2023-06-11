#include <stdlib.h>
#include <stdio.h>

typedef struct arvAVL ArvAVL;

struct arvAVL {
    int info;
    int altura;
    ArvAVL* esq;
    ArvAVL* dir;
};

ArvAVL* novoNo(ArvAVL** arv, int x) {
    ArvAVL* new = malloc(sizeof(ArvAVL));
    if (new == NULL) {
        printf("Erro de alocação de memória");
        return NULL;
    }
    new->info = x;
    new->altura = 0;
    new->esq = NULL;
    new->dir = NULL;
    *arv = new;  // Assign the new node to *arv
    return new;
}

int maior(int a, int b){
    return (a > b) ? a : b;
}

int altura(ArvAVL* arv){
    if(arv == NULL){
        return -1;
    }else{
        return arv->altura;
    }
}

int fatorBalanceamento(ArvAVL *arv){
    if(arv != NULL){
        return altura(arv->esq) - altura(arv->dir);   
    }else{
        return 0;
    }
}

ArvAVL* rEsq(ArvAVL **arv) {
    ArvAVL* aux = (*arv)->dir;
    (*arv)->dir = aux->esq;
    aux->esq = (*arv);
    return aux;
}

ArvAVL* rDir(ArvAVL **arv) {
    ArvAVL* aux = (*arv)->esq;
    (*arv)->esq = aux->dir;
    aux->dir = (*arv);
    return aux;
}

void balancear(ArvAVL** arv) {
    int fb = fatorBalanceamento((*arv));
    if (fb == -2) {
        if (fatorBalanceamento((*arv)->dir) > 0) {
            *arv = rDir(&((*arv)->dir));
        }
        *arv = rEsq(&((*arv)));
    } else if (fb == 2) {
        if (fatorBalanceamento((*arv)->esq) < 0) {
            *arv = rEsq(&((*arv)->esq));
        }
        *arv = rDir(&((*arv)));
    }
}

void imprimir(ArvAVL *arv){
    if(arv != NULL){
        printf("%d ", arv->info);
        imprimir(arv->esq);
        imprimir(arv->dir);
    }
}

ArvAVL *inserir(ArvAVL **arv, int x){
    if((*arv) == NULL){
        novoNo(&((*arv)), x);
    }else{
        if(x < (*arv)->info){
            (*arv)->esq = inserir(&((*arv)->esq), x);
        }else if(x > (*arv)->info){
            (*arv)->dir = inserir(&((*arv)->dir), x);
        }else{
            printf("Valor ja inserido!\n");
        }
    }

    balancear(&((*arv)));

    (*arv)->altura = maior(altura((*arv)->esq), altura((*arv)->dir)) + 1;

    return *arv; 
}
ArvAVL* remover(ArvAVL** arv, int x) {
    if (*arv == NULL) {
        printf("Valor nao encontrado!\n");
    } else {
        if ((*arv)->info == x) {
            if ((*arv)->esq == NULL && (*arv)->dir == NULL) {
                free(*arv);
                *arv = NULL;
                printf("Elemento folha removido: %d !\n", x);
            } else {
                if ((*arv)->esq != NULL && (*arv)->dir != NULL) {
                    ArvAVL* aux = (*arv)->esq;
                    while (aux->dir != NULL) {
                        aux = aux->dir;
                    }
                    (*arv)->info = aux->info;
                    aux->info = x;
                    (*arv)->esq = remover(&((*arv)->esq), x);
                } else {
                    ArvAVL* aux;
                    if ((*arv)->esq != NULL) {
                        aux = (*arv)->esq;
                    } else {
                        aux = (*arv)->dir;
                    }
                    free(*arv);
                    *arv = aux;
                    printf("Elemento com 1 Filho Removido: %d ! \n", x);
                    return aux;
                }
            }
        } else {
            if (x < (*arv)->info) {
                (*arv)->esq = remover(&((*arv)->esq), x);
            } else {
                (*arv)->dir = remover(&((*arv)->dir), x);
            }
        }
    }

    balancear(arv);

    if (*arv != NULL) {
        (*arv)->altura = maior(altura((*arv)->esq), altura((*arv)->dir)) + 1;
    }

    return *arv;
}

int main() {
    ArvAVL*raiz;
    raiz = NULL; 

    inserir(&raiz, 10);
    inserir(&raiz, 18);
    inserir(&raiz, 102);
    inserir(&raiz, 73);
    inserir(&raiz, 8);

    printf("\n");
    imprimir(raiz);
    printf("\n");
    printf("Altura: %d\n", altura(raiz));
    printf("Fator de Balanceamento: %d\n", fatorBalanceamento(raiz));

    printf("\n");
    remover(&raiz, 8);
    printf("Depois da remoção\n");
    printf("\n");
    imprimir(raiz);
    printf("\n");
    printf("Altura: %d\n", altura(raiz));
    printf("Fator de Balanceamento: %d\n", fatorBalanceamento(raiz));

    return 0;
}
