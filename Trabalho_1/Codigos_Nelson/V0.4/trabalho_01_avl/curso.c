#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "curso.h"
#include "disciplina.h"

struct curso {
    int cod_curso;
    char nome_curso[40];
    int quant_blocos;
    int num_sem_disc;
    int altura;
    Disciplina *arv_disciplinas;
    Curso *dir, *esq;
};

// Entrada e inserção de dados
void InsereDadosCursos(Curso **raizArvCurso) {  
    Curso* NovoNoCurso;
    for (int i = 0; i < 30; i++) {
        NovoNoCurso = NovoCurso(*raizArvCurso, "Sistemas de Informacao", 8, 15, i);
        InsereCurso(raizArvCurso, NovoNoCurso);
    }  
}

Curso* NovoCurso(Curso *raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc, int CodCurso) {
    Curso* NovoCurso = (Curso *) malloc(sizeof(Curso));

    if (BuscaCursoCod(raizArvCurso, CodCurso) != NULL) {
        NovoCurso->cod_curso = GeraCodCurso(raizArvCurso);
        puts("OK");
    }
    else {
        NovoCurso->cod_curso = CodCurso;
    }

    strcpy(NovoCurso->nome_curso, NomeCurso);
    NovoCurso->quant_blocos = QuantBlocos;
    NovoCurso->num_sem_disc = NumSemnDisc;
    NovoCurso->arv_disciplinas = NULL;
    InsereDadosDisc(&(NovoCurso->arv_disciplinas), NovoCurso->quant_blocos, NovoCurso->num_sem_disc);
    NovoCurso->dir = NULL;
    NovoCurso->esq = NULL;
    
    return (NovoCurso);
}

//Auxiliaries
void InsereCurso(Curso **raizArvCurso, Curso *NovoCurso) {
    if ((*raizArvCurso) == NULL) {
        *raizArvCurso = NovoCurso;
    }
    else {
        if (NovoCurso->cod_curso > (*raizArvCurso)->cod_curso) {
            InsereCurso(&((*raizArvCurso)->dir), NovoCurso);
        }
        else {
            InsereCurso(&((*raizArvCurso)->esq), NovoCurso);
        }
    }

    BalanceiaArvCursos(raizArvCurso);
    AtualizaAlturaCurso(raizArvCurso);
}

int GeraCodCurso(Curso *raizArvCurso) {
    int CodUnicoCurso;
    do
    {
        CodUnicoCurso = rand() % 1000;
    } while (BuscaCursoCod(raizArvCurso, CodUnicoCurso) != NULL);
    return (CodUnicoCurso);
}

Curso *BuscaCursoCod(Curso *raizArvCurso, int CodCurso) {
    Curso* Encontrou;
    Encontrou = NULL;
    if (raizArvCurso != NULL) {
        if (raizArvCurso->cod_curso == CodCurso) {
            Encontrou = raizArvCurso;   
        }
        else if (CodCurso > raizArvCurso->cod_curso) {
            Encontrou = BuscaCursoCod(raizArvCurso->dir, CodCurso);
        }
        else {
            Encontrou = BuscaCursoCod(raizArvCurso->esq, CodCurso);
        }
    }

    return (Encontrou);
}

int VerificaCursoFolha(Curso *raizArvCurso) {
    int EhFolha = 0;
    if (raizArvCurso->esq == NULL && raizArvCurso->dir == NULL) {
        EhFolha = 1;
    }

    return (EhFolha);
}

int VerificaCursoDoisFilhos(Curso *raizArvCurso) {
    int DoisFilhos = 0;
    if (raizArvCurso->esq != NULL && raizArvCurso->dir != NULL) {
        DoisFilhos = 1;
    }

    return (DoisFilhos);
}

Curso* MaiorFilhoCursoEsq(Curso *raizArvCurso) {
    if (raizArvCurso->dir != NULL) {
        return MaiorFilhoCursoEsq(raizArvCurso->dir);
    }
    else {
        return raizArvCurso;
    }
}

Curso* FilhoCursoLado(Curso *raizArvCurso) {
    if (raizArvCurso->esq != NULL) {
        return (raizArvCurso->esq);
    }
    else {
        return (raizArvCurso->dir);
    }
}

//Balanceamento
void BalanceiaArvCursos(Curso **raizArvCurso) {
    int fb;
    fb = FBCurso(*raizArvCurso);

    if (fb == -2) {
        if (FBCurso((*raizArvCurso)->dir) > 0) {
            RotDirArvCursos(&((*raizArvCurso)->dir));
        }
        RotEsqArvCursos(raizArvCurso);
    }
    else if (fb == 2) {
        if (FBCurso((*raizArvCurso)->esq) < 0) {
            RotEsqArvCursos(&((*raizArvCurso)->esq));
        }
        RotDirArvCursos(raizArvCurso);
    }
}

void RotEsqArvCursos(Curso **raizArvCurso) {
    Curso *aux, *filho;

    aux = (*raizArvCurso)->dir;
    filho = aux->esq;
    aux->esq = *raizArvCurso;
    (*raizArvCurso)->dir = filho;

    AtualizaAlturaCurso(raizArvCurso);
    AtualizaAlturaCurso(&aux);

    *raizArvCurso = aux; 
}

void RotDirArvCursos(Curso **raizArvCurso) {
    Curso *aux, *filho;

    aux = (*raizArvCurso)->esq;
    filho = aux->dir;
    aux->dir = *raizArvCurso;
    (*raizArvCurso)->esq = filho;

    AtualizaAlturaCurso(raizArvCurso);
    AtualizaAlturaCurso(&aux);

    *raizArvCurso = aux;
}

int AltDoNoCurso(Curso *curso) {
    int h;
    if (curso) {
        h = curso->altura;
    }
    else {
        h = -1;
    }
    return (h);
}

int FBCurso(Curso *curso) {
    if (curso) {
        return (AltDoNoCurso(curso->esq) - AltDoNoCurso(curso->dir));
    }
    else {
        return 0;
    }
}

void AtualizaAlturaCurso(Curso **raizArvCurso) {
    (*raizArvCurso)->altura = CalcAltCurso(*raizArvCurso);
}

int CalcAltCurso(Curso *raizArvCurso) {
    int esq, dir, h;

    if (raizArvCurso == NULL) {
        h = -1;
    }
    else {
        esq = CalcAltCurso(raizArvCurso->esq);
        dir = CalcAltCurso(raizArvCurso->dir);

        if (esq > dir) {
            h = esq + 1;
        }
        else {
            h = dir + 1;
        }
    }

    return (h);
}

/*int BuscaValorNoMaisProf(Curso* raizArvCurso) {
    if (raizArvCurso == NULL)
        return -1; // Árvore vazia ou valor inválido

    int esqMaisProf = BuscaValorNoMaisProf(raizArvCurso->esq);
    int dirMaisProf = BuscaValorNoMaisProf(raizArvCurso->dir);

    int valorAtual = raizArvCurso->cod_curso;
    int valorMaisProf = valorAtual;

    if (esqMaisProf > dirMaisProf) {
        if (esqMaisProf > valorAtual)
            valorMaisProf = esqMaisProf;
    } else {
        if (dirMaisProf > valorAtual)
            valorMaisProf = dirMaisProf;
    }

    return valorMaisProf;    
}*/// função criada para auxiliar nos testes

//Impressão de dados
void ImprimeArvCursos(Curso *raizArvCurso, char *situacao) {
    
    if (raizArvCurso != NULL) {
        ImprimeArvCursos(raizArvCurso->esq, situacao);
        printf("Codigo do curso: %d\n", raizArvCurso->cod_curso);
        printf("Nome do curso: %s\n", raizArvCurso->nome_curso);
        printf("Numero de blocos: %d\n", raizArvCurso->quant_blocos);
        printf("Numero de semanas para cada disciplina: %d\n", raizArvCurso->num_sem_disc);
        puts("");
        strcpy(situacao, "Operacao realizada com sucesso!");
        ImprimeArvCursos(raizArvCurso->dir, situacao);

    }

    if (strlen(situacao) == 0) {
        strcpy(situacao, "Nenhum curso na arvore");
    }
}

void ImprimeCursosQuantBlocosIguais(Curso *raizArvCurso, int NumBlocos, char *situacao) {

    if (raizArvCurso != NULL) {
        if (raizArvCurso->quant_blocos == NumBlocos) {
            printf("Curso - %s\n", raizArvCurso->nome_curso);
            printf("Num de blocos: %d\n", raizArvCurso->quant_blocos);
            puts("");
            strcpy(situacao, "Operacao realizada com sucesso!");
        }
        ImprimeCursosQuantBlocosIguais(raizArvCurso->esq, NumBlocos, situacao);
        ImprimeCursosQuantBlocosIguais(raizArvCurso->dir, NumBlocos, situacao);

    }

    if (strlen(situacao) == 0) {
        strcpy(situacao, "Falha na operacao!");
    }
}

void ImprimeDisciplinasCurso(Curso *raizArvCurso, int CodCurso, char *situacao) {
    Curso *AuxCurso;
    if ((AuxCurso = (BuscaCursoCod(raizArvCurso, CodCurso))) != NULL) {
        ImprimeArvDisc(AuxCurso->arv_disciplinas, situacao);
    }
    else {
        strcpy(situacao, "Falha na operacao! Curso nao encontrado!");
    }  
}

void ImprimeCurso(Curso *raizArvCurso, int CodCurso, char *situacao) {
    Curso *AuxCurso;

    if ((AuxCurso = BuscaCursoCod(raizArvCurso, CodCurso)) != NULL) {
        printf("Curso - %s\n", AuxCurso->nome_curso);
        printf("Codigo: %d\n", AuxCurso->cod_curso);
        printf("Numero de blocos: %d\n", AuxCurso->quant_blocos);
        printf("Numero de semanas para cada disciplina: %d\n", AuxCurso->num_sem_disc);
        puts("");
        strcpy(situacao, "Operacao realizada com sucesso!");
    }
    else {
        strcpy(situacao, "Falha na operacao! Curso nao encontrado!");
    }
}

void ImprimeDisciplinaCurso(Curso *raizArvCurso, int CodCurso, int CodDisc, char *situacao) {
    Curso *AuxCurso;
    if (raizArvCurso != NULL) {
        if ((AuxCurso = BuscaCursoCod(raizArvCurso, CodCurso)) != NULL) {
            Disciplina *AuxDisciplina;
            if ((AuxDisciplina = BuscaDiscCod(AuxCurso->arv_disciplinas, CodDisc)) != NULL) {
                ImprimeDisc(AuxDisciplina);
                strcpy(situacao, "Operacao realizada com sucesso!");
            }
            else {
                strcpy(situacao, "Falha na operacao! Disciplina nao encontrada!");
            }
        }
        else {
            strcpy(situacao, "Falha na operacao! Curso nao encontrado!");
        }
    }
    
    if (strlen(situacao) == 0) {
        strcpy(situacao, "Falha na operacao! Nenhum curso na arvore");
    }
}

void ImprimeDiscMesmoBloco(Curso *raizArvCurso, int CodCurso, int Bloco, char *situacao) {
    if (raizArvCurso != NULL) {
        Curso *AuxCurso;
        if ((AuxCurso = BuscaCursoCod(raizArvCurso, CodCurso)) != NULL) {
            if (Bloco <= AuxCurso->quant_blocos) {
                ImprimeDiscBlocosIguais(AuxCurso->arv_disciplinas, Bloco, situacao);    
            }
            else {
                strcpy(situacao, "Falha na operacao! Num do bloco eh maior que a quantidade de blocos do curso.");    
            }
        }
        else {
            strcpy(situacao, "Falha na operacao! Curso nao encontrado!");    
        }
    }
}

void ImprimeDiscMesmaCH(Curso *raizArvCurso, int CodCurso, int CargaHoraria, char *situacao) {
    if (raizArvCurso != NULL) {
        Curso *AuxCurso;
        if ((AuxCurso = BuscaCursoCod(raizArvCurso, CodCurso)) != NULL) {
            if (CargaHoraria % AuxCurso->num_sem_disc == 0) {
                ImprimeDiscCHIguais(AuxCurso->arv_disciplinas, CargaHoraria, situacao);    
            }
            else {
                strcpy(situacao, "Falha na operacao! Num da CH nao eh multiplo do num de semanas do curso.");    
            }
        }
        else {
            strcpy(situacao, "Falha na operacao! Curso nao encontrado!");    
        }
    }
}

// Remoção
void RemoveDiscCurso(Curso *raizArvCurso, int CodCurso, int CodDisc, char *situacao) {
    if (raizArvCurso != NULL) {
        Curso *AuxCurso;
        if ((AuxCurso = (BuscaCursoCod(raizArvCurso, CodCurso))) != NULL) {
            RemoveDisc(&(AuxCurso->arv_disciplinas), CodDisc, situacao);
        }
        else {
            strcpy(situacao, "Falha na operacao! Curso nao encontrado!");    
        }
    }

    if (strlen(situacao) == 0) {
        strcpy(situacao, "Falha na operacao!");    
    }
}

int RemoveCurso(Curso **raizArvCurso, int CodCurso, char *situacao) {
    int removeu = 1;

    if ((*raizArvCurso) != NULL) {
        Curso *Aux, *Filho;

        if ((*raizArvCurso)->cod_curso == CodCurso) {
            if ((*raizArvCurso)->arv_disciplinas != NULL) {
                strcpy(situacao, "Falha na operacao! Curso possui disciplinas cadastradas!");    
            }
            else {
                if (VerificaCursoFolha(*raizArvCurso)) {
                    Aux = (*raizArvCurso);
                    (*raizArvCurso) = NULL;
                }
                else if (VerificaCursoDoisFilhos(*raizArvCurso)) {
                    Filho = MaiorFilhoCursoEsq(*raizArvCurso);
                    Aux = (*raizArvCurso);
                    Filho->dir = (*raizArvCurso)->dir;
                    (*raizArvCurso) = (*raizArvCurso)->esq;
                }
                else {
                    Filho = FilhoCursoLado(*raizArvCurso);
                    Aux = (*raizArvCurso);
                    (*raizArvCurso) = Filho;
                }
                free(Aux);
                removeu = 0;
                strcpy(situacao, "Operacao realizada com sucesso!");
            } 
        }
        else if ((*raizArvCurso)->cod_curso > CodCurso) {
            RemoveCurso(&((*raizArvCurso)->esq), CodCurso, situacao);
        }
        else {
            RemoveCurso(&((*raizArvCurso)->dir), CodCurso, situacao);    
        }
    }
    
    if (removeu == 0 && (*raizArvCurso) != NULL) {
        BalanceiaArvCursos(raizArvCurso);
        AtualizaAlturaCurso(raizArvCurso);
    } 

    if (strlen(situacao) == 0) {
        strcpy(situacao, "Falha na operacao! Curso nao encontrada"); 
    }

    return (removeu);
}