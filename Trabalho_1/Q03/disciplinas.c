#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ImpDisciplinas.h"

struct disciplinas {
    int cod_disc;
    char nome_disc[50];
    int bloco;
    int carga_horaria;
    int altura;
    Disciplinas *esq, *dir;
};
int maiorD(int a, int b){
    return (a > b) ? a : b;
}

int alturaD(Disciplinas *raizArvDisc){
    if(raizArvDisc == NULL){
        return -1;
    }else{
        return raizArvDisc->altura;
    }
}

int fatorBalanceamentoDisc(Disciplinas *raizArvDisc){
    if(raizArvDisc != NULL){
        return alturaD(raizArvDisc->esq) - alturaD(raizArvDisc->dir);   
    }else{
        return 0;
    }
}

Disciplinas* rEsqD(Disciplinas **raizArvDisc) {
    Disciplinas* aux = (*raizArvDisc)->dir;
    (*raizArvDisc)->dir = aux->esq;
    aux->esq = (*raizArvDisc);
    return aux;
}

Disciplinas* rDirD(Disciplinas **raizArvDisc) {
    Disciplinas* aux = (*raizArvDisc)->esq;
    (*raizArvDisc)->esq = aux->dir;
    aux->dir = (*raizArvDisc);
    return aux;
}

void balancearDisc(Disciplinas **raizArvDisc) {
    int fb = fatorBalanceamentoDisc((*raizArvDisc));
    if (fb == -2) {
        if (fatorBalanceamentoDisc((*raizArvDisc)->dir) > 0) {
            *raizArvDisc = rDirD(&((*raizArvDisc)->dir));
        }
        *raizArvDisc = rEsqD(&((*raizArvDisc)));
    } else if (fb == 2) {
        if (fatorBalanceamentoDisc((*raizArvDisc)->esq) < 0) {
            *raizArvDisc = rEsqD(&((*raizArvDisc)->esq));
        }
        *raizArvDisc = rDirD(&((*raizArvDisc)));
    }
}


void InsereDadosDisc(Disciplinas **raizArvDisc) {
    EntradaDadosDisc(&(*raizArvDisc), "maneira", 2, 60);
    EntradaDadosDisc(&(*raizArvDisc), "paia", 2, 15);
    EntradaDadosDisc(&(*raizArvDisc), "legalzona", 1, 60);
    EntradaDadosDisc(&(*raizArvDisc), "essaEhRuim", 3, 20);
    EntradaDadosDisc(&(*raizArvDisc), "essaEhpaia", 3, 10);
}

void EntradaDadosDisc(Disciplinas **raizArvDisc, char *NomeDisc, int Bloco, int CargaHoraria) {
    Disciplinas* NovaDisc = (Disciplinas *) malloc(sizeof(Disciplinas));

    NovaDisc->cod_disc = GeraCodDisc((*raizArvDisc));
    strcpy(NovaDisc->nome_disc, NomeDisc);
    NovaDisc->bloco = Bloco;
    NovaDisc->carga_horaria = CargaHoraria;
    NovaDisc->esq = NULL;
    NovaDisc->dir = NULL;

    InsereDisc(&(*raizArvDisc), NovaDisc);
}

void InsereDisc(Disciplinas **raizArvDisc, Disciplinas *NovaDisc) {
    if ((*raizArvDisc) == NULL) {
        (*raizArvDisc) = NovaDisc;
    }
    else {
        if (NovaDisc->cod_disc > (*raizArvDisc)->cod_disc) {
            InsereDisc(&((*raizArvDisc)->dir), NovaDisc);
        }
        else {
            InsereDisc(&((*raizArvDisc)->esq), NovaDisc);
        }
    }
    balancearDisc(&((*raizArvDisc)));
    (*raizArvDisc)->altura = maiorD(alturaD((*raizArvDisc)->esq), alturaD((*raizArvDisc)->dir)) + 1;
}

int GeraCodDisc(Disciplinas *raizArvDisc) {
    int cod_unico_disc;

    do
    {
        cod_unico_disc = rand() % 1000;
    } while (BuscaDiscCod(raizArvDisc, cod_unico_disc) != NULL);

    return cod_unico_disc;
}

Disciplinas* BuscaDiscCod(Disciplinas *raizArvDisc, int CodDisc) {
    Disciplinas *AuxDisc;
    AuxDisc = NULL;

    if (raizArvDisc != NULL) {
        if (CodDisc == raizArvDisc->cod_disc) {
            AuxDisc = raizArvDisc;
        }
        else if (CodDisc > raizArvDisc->cod_disc) {
            AuxDisc = BuscaDiscCod(raizArvDisc->dir, CodDisc);
        }
        else {
            AuxDisc = BuscaDiscCod(raizArvDisc->esq, CodDisc);
        }
    }

    return (AuxDisc);
}

void ImprimeArvDisc(Disciplinas *raizArvDisc) {
    if (raizArvDisc != NULL) {
        ImprimeArvDisc(raizArvDisc->esq);
        printf("---------------------\n");
        printf("Cod: %d\n", raizArvDisc->cod_disc);
        printf("Nome: %s\n", raizArvDisc->nome_disc);
        printf("Bloco: %d\n", raizArvDisc->bloco);
        printf("Carga horaria: %d\n", raizArvDisc->carga_horaria);
        printf("---------------------\n");
        ImprimeArvDisc(raizArvDisc->dir);
    }
}

void ImprimeDiscMsmBloco(Disciplinas *raizArvDisc, int Bloco) {
        if (raizArvDisc != NULL) {
            ImprimeDiscMsmBloco(raizArvDisc->esq, Bloco);
            if (raizArvDisc->bloco == Bloco) {
                printf("---------------------\n");
                printf("Cod: %d\n", raizArvDisc->cod_disc);
                printf("Nome: %s\n", raizArvDisc->nome_disc);
                printf("Bloco: %d\n", raizArvDisc->bloco);
                printf("Carga horaria: %d\n", raizArvDisc->carga_horaria);
                printf("---------------------\n");
            }
            ImprimeDiscMsmBloco(raizArvDisc->dir, Bloco);
        }
}


void ImprimeDisc(Disciplinas *DisciplinaCurso) {
    printf("---------------------\n");
    printf("Cod: %d\n", DisciplinaCurso->cod_disc);
    printf("Disciplinas - %s\n", DisciplinaCurso->nome_disc);
    printf("Bloco: %d\n", DisciplinaCurso->bloco);
    printf("Carga horaria: %d\n", DisciplinaCurso->carga_horaria);
    printf("---------------------\n");    
}

void ImprimeDiscCargaHoraria(Disciplinas *raizArvDisc, int ch){
    if (raizArvDisc != NULL) {
        ImprimeDiscCargaHoraria(raizArvDisc->esq, ch);
        if (raizArvDisc->carga_horaria == ch) {
            printf("---------------------\n");
            printf("Cod: %d\n", raizArvDisc->cod_disc);
            printf("Nome: %s\n", raizArvDisc->nome_disc);
            printf("Bloco: %d\n", raizArvDisc->bloco);
            printf("Carga horaria: %d\n", raizArvDisc->carga_horaria);
            printf("---------------------\n");
        }
        ImprimeDiscCargaHoraria(raizArvDisc->dir, ch);
    }
}

Disciplinas* RemoveDisc(Disciplinas* raizArvDisc, int cod_disciplina) {
    Disciplinas* auxDisc = raizArvDisc;
    Disciplinas* auxDisc2 = NULL;

    while (auxDisc != NULL) {
        if (cod_disciplina == auxDisc->cod_disc) {
            if (auxDisc->esq == NULL && auxDisc->dir == NULL) {
                if (auxDisc2->esq == auxDisc) {
                    auxDisc2->esq = NULL;
                }
                else {
                    auxDisc2->dir = NULL;
                }
                free(auxDisc);
                auxDisc = NULL;
            }
            else if (auxDisc->esq == NULL && auxDisc->dir != NULL) {
                if (auxDisc2->esq == auxDisc) {
                    auxDisc2->esq = auxDisc->dir;
                }
                else {
                    auxDisc2->dir = auxDisc->dir;
                }
                free(auxDisc);
                auxDisc = NULL;
            }
            else if (auxDisc->esq != NULL && auxDisc->dir == NULL) {
                if (auxDisc2->esq == auxDisc) {
                    auxDisc2->esq = auxDisc->esq;
                }
                else {
                    auxDisc2->dir = auxDisc->esq;
                }
                free(auxDisc);
                auxDisc = NULL;
            }
            else {
                auxDisc2 = auxDisc;
                auxDisc = auxDisc->esq;
                while (auxDisc->dir != NULL) {
                    auxDisc2 = auxDisc;
                    auxDisc = auxDisc->dir;
                }
                auxDisc2->dir = NULL;
                free(auxDisc);
                auxDisc = NULL;
            }
        }
        else if (cod_disciplina > auxDisc->cod_disc) {
            auxDisc2 = auxDisc;
            auxDisc = auxDisc->dir;
        }
        else {
            auxDisc2 = auxDisc;
            auxDisc = auxDisc->esq;
        }
    }
    return raizArvDisc;
}
