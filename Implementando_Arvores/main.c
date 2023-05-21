#include <stdio.h>
#include <stdlib.h>

typedef struct Arvbb{
    int info;
    struct Arvbb *esq, *dir;
}ArvBB;

ArvBB criaArvore(ArvBB *raiz){
    raiz = NULL;
}

void inserir(ArvBB **raiz, int valor){
    if((*raiz) == NULL){
        ArvBB *new = (ArvBB *) malloc(sizeof(ArvBB));
        new->info = valor;
        new->dir = NULL;
        new->esq = NULL;
        (*raiz) = new;

    }else{
        if((*raiz)->info > valor){
            inserir(&((*raiz)->esq), valor);
        }else{
            inserir(&((*raiz)->dir), valor);
        }
    }
}

void mostrarArvore(ArvBB *raiz){
    if(raiz != NULL){
        printf("%d \n", raiz->info);
        mostrarArvore(raiz->esq);
        mostrarArvore(raiz->dir);
    }
}

ArvBB *remover(ArvBB **raiz, int valor) {
    if ((*raiz) == NULL) {
        puts("Valor nao encontrado!!!");
        return NULL;
    }
    else {
        if ((*raiz)->info == valor) {
            if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
                free((*raiz));
                return NULL;
            } else {
                if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
                    ArvBB *aux;
                    if ((*raiz)->esq != NULL) {
                        aux = (*raiz)->esq;
                    } else {
                        aux = (*raiz)->dir;
                    }
                    free((*raiz));
                    return aux;
                }
            }
        } else {
            if (valor < (*raiz)->info) {
                (*raiz)->esq = remover(&((*raiz)->esq), valor);
            } else {
                (*raiz)->dir = remover(&((*raiz)->dir), valor);
            }
            return (*raiz);
        }
    }
}

int main(){
    ArvBB *arvore;
    arvore = NULL;

    inserir(&(arvore), 50);
    inserir(&(arvore), 35);
    inserir(&(arvore), 30);
    inserir(&(arvore), 25);
    inserir(&(arvore), 100);

    remover(&(arvore), 30);

    mostrarArvore(arvore);
}