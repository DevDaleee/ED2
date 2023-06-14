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
    int altura;
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

    BalanceiaArvDisc(raizArvDisc);
    AtualizaAlturaDisc(raizArvDisc);
}

//Auxiliaries
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

//Balanceamento
void BalanceiaArvDisc(Disciplina **raizArvDisc) {
        int fb;
    fb = FBDisc(*raizArvDisc);

    if (fb == -2) {
        if (FBDisc((*raizArvDisc)->dir) > 0) {
            RotDirArvDisc(&((*raizArvDisc)->dir));
        }
        RotEsqArvDisc(raizArvDisc);
    }
    else if (fb == 2) {
        if (FBDisc((*raizArvDisc)->esq) < 0) {
            RotEsqArvDisc(&((*raizArvDisc)->esq));
        }
        RotDirArvDisc(raizArvDisc);
    }
}

void RotEsqArvDisc(Disciplina **raizArvDisc) {
    Disciplina *aux, *filho;

    aux = (*raizArvDisc)->dir;
    filho = aux->esq;
    aux->esq = *raizArvDisc;
    (*raizArvDisc)->dir = filho;

    AtualizaAlturaDisc(raizArvDisc);
    AtualizaAlturaDisc(&aux);

    *raizArvDisc = aux; 
}

void RotDirArvDisc(Disciplina **raizArvDisc) {
    Disciplina *aux, *filho;

    aux = (*raizArvDisc)->esq;
    filho = aux->dir;
    aux->dir = *raizArvDisc;
    (*raizArvDisc)->esq = filho;

    AtualizaAlturaDisc(raizArvDisc);
    AtualizaAlturaDisc(&aux);

    *raizArvDisc = aux;
}

int AltDoNoDisc(Disciplina *Disc) {
    int h;
    if (Disc) {
        h = Disc->altura;
    }
    else {
        h = -1;
    }
    return (h);
}

int FBDisc(Disciplina *Disc) {
    if (Disc) {
        return (AltDoNoDisc(Disc->esq) - AltDoNoDisc(Disc->dir));
    }
    else {
        return 0;
    }
}

void AtualizaAlturaDisc(Disciplina **raizArvDisc) {
    (*raizArvDisc)->altura = CalcAltDisc(*raizArvDisc);
}

int CalcAltDisc(Disciplina *raizArvDisc) {
    int esq, dir, h;

    if (raizArvDisc == NULL) {
        h = -1;
    }
    else {
        esq = CalcAltDisc(raizArvDisc->esq);
        dir = CalcAltDisc(raizArvDisc->dir);

        if (esq > dir) {
            h = esq + 1;
        }
        else {
            h = dir + 1;
        }
    }

    return (h);
}

//Impressão de dados
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
int RemoveDisc(Disciplina **raizArvDisc, int CodDisc, char *situacao) {
    int removeu = 1;
    
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
            removeu = 0;
            strcpy(situacao, "Operacao realizada com sucesso!");
        }
        else if ((*raizArvDisc)->cod_disc > CodDisc) {
            RemoveDisc(&((*raizArvDisc)->esq), CodDisc, situacao);
        }
        else {
            RemoveDisc(&((*raizArvDisc)->dir), CodDisc, situacao);    
        }

    }

    if (removeu == 0 && *raizArvDisc != NULL) {
        BalanceiaArvDisc(raizArvDisc);
        AtualizaAlturaDisc(raizArvDisc);
    }

    if (strlen(situacao) == 0) {
        strcpy(situacao, "Falha na operacao! Disciplina nao encontrada"); 
    }
}