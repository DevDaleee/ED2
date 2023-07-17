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
void InsereDadosDisc(Disciplina **raizArvDisc, int QuantBlocosCurso, int QntSemDisc) {
    Disciplina* NovoNoDisc;

    for (int i = 0; i < 30; i++) {
        NovoNoDisc = NovaDisc(*raizArvDisc, "Estruturas de Dados II", 4, 60, QuantBlocosCurso, QntSemDisc);
        InsereDisc(raizArvDisc, NovoNoDisc);
    }   
}

Disciplina* NovaDisc(Disciplina *raizArvDisc, char *NomeDisc, int Bloco, int CargaHoraria, int QuantBlocosCurso, int QntSemDisc) {
    
    if ((VerificaBlocoDisc(QuantBlocosCurso, Bloco) == 0) || (VerificaCH(QntSemDisc, CargaHoraria) == 0)) {
       printf("ERRO ao alocar disciplina - %s\n", NomeDisc);
    }
    else {
        Disciplina* NovaDisc = (Disciplina *) malloc(sizeof(Disciplina));

        NovaDisc->cod_disc = GeraCodDisc(raizArvDisc);
        strcpy(NovaDisc->nome_disc, NomeDisc);
        NovaDisc->bloco = Bloco;
        NovaDisc->carga_horaria = CargaHoraria;
        NovaDisc->esq = NULL;
        NovaDisc->dir = NULL;

        return (NovaDisc);
    }
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

int VerificaDiscFolha(Disciplina *raizArvDisc) {
    int EhFolha = 0;
    if (raizArvDisc->esq == NULL && raizArvDisc->dir == NULL) {
        EhFolha = 1;
    }
    
    return (EhFolha);
}

int VerificaDiscDoisFilhos(Disciplina *raizArvDisc) {
    int DoisFilhos = 0;
    if (raizArvDisc->dir != NULL && raizArvDisc->esq != NULL) {
        DoisFilhos = 1;
    }

    return (DoisFilhos);
}

int VerificaBlocoDisc(int QuantBlocosCurso, int BlocoDisc) {
    int Situacao = 0;

    if (BlocoDisc > 0 && BlocoDisc <= QuantBlocosCurso) {
        Situacao = 1;
    }
    return (Situacao);
}

int VerificaCH(int NumSemDisc, int CHDisc) {
    int Situacao = 0;

    if (CHDisc % NumSemDisc == 0) {
        Situacao = 1;
    }
    return (Situacao);
}

Disciplina* MaiorFilhoDiscEsq(Disciplina *raizArvDisc) {
    if (raizArvDisc->dir != NULL){
        return MaiorFilhoDiscEsq(raizArvDisc->dir);
    }
    else {
        return (raizArvDisc);
    }
}

Disciplina* FilhoDiscLado(Disciplina *raizArvDisc) {
    if (raizArvDisc->esq != NULL) {
        return (raizArvDisc->esq);
    }
    else {
        return (raizArvDisc->dir);    
    }
}


// Impressão de dados
void ImprimeArvDisc(Disciplina *raizArvDisc, char *situacao) {
    if (raizArvDisc != NULL) {
        ImprimeArvDisc(raizArvDisc->esq, situacao);
        printf("Disciplina - %s\n", raizArvDisc->nome_disc);
        printf("Codigo: %d\n", raizArvDisc->cod_disc);
        printf("Bloco: %d\n", raizArvDisc->bloco);
        printf("Carga horaria: %d\n", raizArvDisc->carga_horaria);
        puts("");
        strcpy(situacao, "Operacao realizada com sucesso!");
        ImprimeArvDisc(raizArvDisc->dir, situacao);
    }

    if (strlen(situacao) == 0) {
        strcpy(situacao, "Nenhuma disciplina encontrada!");
    }
}

void ImprimeDisc(Disciplina *DisciplinaCurso) {
    if (DisciplinaCurso != NULL) {
        puts(""); 
        printf("Disciplina - %s\n", DisciplinaCurso->nome_disc);
        printf("Codigo: %d\n", DisciplinaCurso->cod_disc);
        printf("Bloco: %d\n", DisciplinaCurso->bloco);
        printf("Carga horaria: %d\n", DisciplinaCurso->carga_horaria);
        puts(""); 
    }   
}

void ImprimeDiscBlocosIguais(Disciplina *raizArvDisc, int Bloco, char *situacao) {
    if (raizArvDisc != NULL) {
        if (raizArvDisc->bloco == Bloco) {
            ImprimeDisc(raizArvDisc);
            strcpy(situacao, "Operacao realizada com sucesso!");
        }
        ImprimeDiscBlocosIguais(raizArvDisc->esq, Bloco, situacao);
        ImprimeDiscBlocosIguais(raizArvDisc->dir, Bloco, situacao);
    }
    
    if (strlen(situacao) == 0) {
        strcpy(situacao, "Falha na operacao!");    
    }
}

void ImprimeDiscCHIguais(Disciplina *raizArvDisc, int CargaHoraria, char *situacao) {
    if (raizArvDisc != NULL) {
        if (raizArvDisc->carga_horaria == CargaHoraria) {
            ImprimeDisc(raizArvDisc);
            strcpy(situacao, "Operacao realizada com sucesso!");
        }
        ImprimeDiscCHIguais(raizArvDisc->esq, CargaHoraria, situacao);
        ImprimeDiscCHIguais(raizArvDisc->dir, CargaHoraria, situacao);
    }
    
    if (strlen(situacao) == 0) {
        strcpy(situacao, "Falha na operacao!");    
    }    
}


// Remoção
void RemoveDisc(Disciplina **raizArvDisc, int CodDisc, char *situacao) {
    if ((*raizArvDisc) != NULL) {
        Disciplina *Aux, *Filho;

        if ((*raizArvDisc)->cod_disc == CodDisc) {
            if (VerificaDiscFolha(*raizArvDisc)) {
                Aux = (*raizArvDisc);
                (*raizArvDisc) = NULL;
            }
            else if (VerificaDiscDoisFilhos(*raizArvDisc)) {
                Filho = MaiorFilhoDiscEsq(*raizArvDisc);
                Aux = (*raizArvDisc);
                Filho->dir = (*raizArvDisc)->dir;
                (*raizArvDisc) = (*raizArvDisc)->esq;
            }
            else {
                Filho = FilhoDiscLado(*raizArvDisc);
                Aux = (*raizArvDisc);
                (*raizArvDisc) = Filho;
            }
            free(Aux);
            strcpy(situacao, "Operacao realizada com sucesso!");
        }
        else if ((*raizArvDisc)->cod_disc > CodDisc) {
            RemoveDisc(&((*raizArvDisc)->esq), CodDisc, situacao);
        }
        else {
            RemoveDisc(&((*raizArvDisc)->dir), CodDisc, situacao);    
        }

    }

    if (strlen(situacao) == 0) {
        strcpy(situacao, "Falha na operacao! Disciplina nao encontrada"); 
    }
}