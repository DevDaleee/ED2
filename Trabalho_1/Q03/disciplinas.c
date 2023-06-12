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

int maxDisc(int a, int b) {
    return (a > b) ? a : b;
}

int getHeightDisciplinas(Disciplinas* raizArvDisc) {
    if (raizArvDisc == NULL)
        return 0;
    return maxDisc(getHeightDisciplinas(raizArvDisc->esq), getHeightDisciplinas(raizArvDisc->dir)) + 1;
}

int getBalanceDisciplinas(Disciplinas* raizArvDisc) {
    if (raizArvDisc == NULL)
        return 0;
    return getHeightDisciplinas(raizArvDisc->esq) - getHeightDisciplinas(raizArvDisc->dir);
}

Disciplinas* RDDisc(Disciplinas* y) {
    Disciplinas* x = y->esq;
    Disciplinas* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    return x;
}

Disciplinas* REDisc(Disciplinas* x) {
    Disciplinas* y = x->dir;
    Disciplinas* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    return y;
}

void balanceTreeDisciplinas(Disciplinas** raizArvDisc) {
    int balance = getBalanceDisciplinas(*raizArvDisc);

    if (balance > 1) {
        if (getBalanceDisciplinas((*raizArvDisc)->esq) < 0) {
            (*raizArvDisc)->esq = REDisc((*raizArvDisc)->esq);
        }
        *raizArvDisc = RDDisc(*raizArvDisc);
    } else if (balance < -1) {
        if (getBalanceDisciplinas((*raizArvDisc)->dir) > 0) {
            (*raizArvDisc)->dir = RDDisc((*raizArvDisc)->dir);
        }
        *raizArvDisc = REDisc(*raizArvDisc);
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
    balanceTreeDisciplinas(&((*raizArvDisc)));
    (*raizArvDisc)->altura = maxDisc(getHeightDisciplinas((*raizArvDisc)->esq), getHeightDisciplinas((*raizArvDisc)->dir)) + 1;
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

void RemoveDisc(Disciplinas** raizArvDisc, int cod_disciplina) {
    Disciplinas* raiz = *raizArvDisc;
    Disciplinas* filho = NULL;
    Disciplinas* atual = raiz;

    while (atual != NULL && atual->cod_disc != cod_disciplina) {
        filho = atual;
        if (cod_disciplina < atual->cod_disc) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if (atual == NULL) {
        return;
    }

    if (atual->esq == NULL && atual->dir == NULL) {
        if (filho == NULL) {
            (*raizArvDisc) = NULL;
        } else if (filho->esq == atual) {
            filho->esq = NULL;
        } else {
            filho->dir = NULL;
        }
        free(atual);
    } else if (atual->esq == NULL || atual->dir == NULL) {
        Disciplinas* child = (atual->esq != NULL) ? atual->esq : atual->dir;
        if (filho == NULL) {
            *raizArvDisc = child;
        } else if (filho->esq == atual) {
            filho->esq = child;
        } else {
            filho->dir = child;
        }
        free(atual);
    } else {
        Disciplinas* new = atual;
        Disciplinas* aux2 = atual->dir;

        while (aux2->esq != NULL) {
            new = aux2;
            aux2 = aux2->esq;
        }

        if (new != atual) {
            new->esq = aux2->dir;
        } else {
            new->dir = aux2->dir;
        }

        atual->cod_disc = aux2->cod_disc;
        free(aux2);
    }

    balanceTreeDisciplinas(raizArvDisc);

}
