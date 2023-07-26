#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "impLLRB.h"
#include "impLPalavra.h"

typedef struct Lpalavra {
    char Palavra[50];
    rLinhas *ListaLinhas;
} Palavra;

typedef struct arb {
    Palavra info;
    ArvRN *esq;
    ArvRN *dir;
    char cor;
}ArvRN;

void rEsquerda(ArvRN **RaizArv) {
    ArvRN *Aux, *Filho;
    Aux = (*RaizArv)->dir;
    Filho = Aux->esq;
    Aux->esq = (*RaizArv);
    (*RaizArv)->dir = Filho;
    Aux->cor = (*RaizArv)->cor;
    (*RaizArv)->cor = 'R';
    (*RaizArv) = Aux;
}

void rDireita(ArvRN **RaizArv) {
    ArvRN *Aux, *Filho;
    Aux = (*RaizArv)->esq;
    Filho = (Aux)->dir;
    Aux->dir = (*RaizArv);
    (*RaizArv)->esq = Filho;
    Aux->cor = (*RaizArv)->cor;
    (*RaizArv)->cor = 'R';
    (*RaizArv) = Aux;
}

void trocaCor(ArvRN **RaizArv) {
    (*RaizArv)->cor = 'R';
    (*RaizArv)->esq->cor = 'B';
    (*RaizArv)->dir->cor = 'B';
}

char verificaCor(ArvRN *RaizArv){
    if(RaizArv == NULL){
        return 'B';
    } else {
        return RaizArv->cor;
    }
}

void balancearLLRB(ArvRN **RaizArv) {
    if (verificaCor((*RaizArv)->dir) == 'R' && verificaCor((*RaizArv)->esq) == 'B'){
        rEsquerda(RaizArv);
    }
    if (verificaCor((*RaizArv)->esq) == 'R' && verificaCor((*RaizArv)->esq->esq) == 'R') {
        rDireita(RaizArv);
    }
    if (verificaCor((*RaizArv)->esq) == 'R' && verificaCor((*RaizArv)->dir) == 'R') {
        trocaCor(RaizArv);
    }
}

void EntradasDados(ArvRN **RaizArv, char *valor, int repetidas) {
    if (*RaizArv == NULL) {
        *RaizArv = (ArvRN*) malloc(sizeof(ArvRN));
        strcpy((*RaizArv)->info.Palavra, valor);
        (*RaizArv)->esq = NULL;
        (*RaizArv)->dir = NULL;
        (*RaizArv)->info.ListaLinhas = NULL;
        (*RaizArv)->cor = 'R';
        InserirLista(&((*RaizArv)->info.ListaLinhas), repetidas);
    } else {
        int valorPalavra = strcasecmp(valor, (*RaizArv)->info.Palavra);

        if(valorPalavra == 0){
            InserirLista(&((*RaizArv)->info.ListaLinhas), repetidas);
        } else if (valorPalavra < 0) {
            EntradasDados(&((*RaizArv)->esq), valor, repetidas);
        } else {
            EntradasDados(&((*RaizArv)->dir), valor, repetidas);   
        }
        balancearLLRB(RaizArv);
    }
}

void BuscarPalavra(ArvRN *RaizArv, char *valor){
    if(RaizArv != NULL){
        int valorPalavra = strcasecmp(valor, RaizArv->info.Palavra);
        if(valorPalavra == 0){
            ImprimirLista(RaizArv->info.ListaLinhas);
        } else if (valorPalavra < 0) {
            BuscarPalavra(RaizArv->esq, valor);
        } else {
            BuscarPalavra(RaizArv->dir, valor);   
        }
    }
}

void inserir(ArvRN **RaizArv, char *valor, int repetidas) {
    EntradasDados(RaizArv, valor, repetidas);
    if (RaizArv != NULL) {
        (*RaizArv)->cor = 'B';
    }
}

void ImprimeArvoreInOrdemLLRB(ArvRN *RaizArv) {
    if (RaizArv != NULL) {
        ImprimeArvoreInOrdemLLRB(RaizArv->esq);
        printf("%s ", RaizArv->info.Palavra);
        printf("%c\n", RaizArv->cor);
        ImprimeArvoreInOrdemLLRB(RaizArv->dir);
    }
}

void ImprimirListaLinhas(ArvRN *RaizArv){
    if(RaizArv != NULL){
        ImprimirListaLinhas(RaizArv->esq);
        ImprimirLista(RaizArv->info.ListaLinhas);
        ImprimirListaLinhas(RaizArv->dir);
    }
}