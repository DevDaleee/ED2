#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "disciplina.h"

struct disciplina {
    int cod_disc;
    char nome_disc[50];
    int bloco;
    int carga_horaria;
    Disciplina *esq, *dir;
};

// Entrada e inserção de dados
void InsereDadosDisc(Disciplina **raizArvDisc) {
    EntradaDadosDisc(&(*raizArvDisc), "maneira", 2, 60);
    EntradaDadosDisc(&(*raizArvDisc), "paia", 2, 15);
}

void EntradaDadosDisc(Disciplina **raizArvDisc, char *NomeDisc, int Bloco, int CargaHoraria) {
    Disciplina* NovaDisc = (Disciplina *) malloc(sizeof(Disciplina));

    NovaDisc->cod_disc = GeraCodDisc((*raizArvDisc));
    strcpy(NovaDisc->nome_disc, NomeDisc);
    NovaDisc->bloco = Bloco;
    NovaDisc->carga_horaria = CargaHoraria;
    NovaDisc->esq = NULL;
    NovaDisc->dir = NULL;

    InsereDisc(&(*raizArvDisc), NovaDisc);
}

void InsereDisc(Disciplina **raizArvDisc, Disciplina *NovaDisc) {
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
}

int GeraCodDisc(Disciplina *raizArvDisc) {
    int cod_unico_disc;

    do
    {
        cod_unico_disc = rand() % 1000;
    } while (BuscaDiscCod(raizArvDisc, cod_unico_disc) != NULL);

    return cod_unico_disc;
}

Disciplina* BuscaDiscCod(Disciplina *raizArvDisc, int CodDisc) {
    Disciplina *AuxDisc;
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

void ImprimeArvDisc(Disciplina *raizArvDisc) {
    if (raizArvDisc != NULL) {
        ImprimeArvDisc(raizArvDisc->esq);
        printf("Cod: %d\n", raizArvDisc->cod_disc);
        printf("Nome: %s\n", raizArvDisc->nome_disc);
        printf("Bloco: %d\n", raizArvDisc->bloco);
        printf("Carga horaria: %d\n", raizArvDisc->carga_horaria);
        ImprimeArvDisc(raizArvDisc->dir);
    }
}

void ImprimeDisc(Disciplina *DisciplinaCurso) {
    printf("Cod: %d\n", DisciplinaCurso->cod_disc);
    printf("Disciplina - %s\n", DisciplinaCurso->nome_disc);
    printf("Bloco: %d\n", DisciplinaCurso->bloco);
    printf("Carga horaria: %d\n", DisciplinaCurso->carga_horaria);    
}