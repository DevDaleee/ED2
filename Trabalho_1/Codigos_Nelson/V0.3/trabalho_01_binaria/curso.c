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
    Disciplina *arv_disciplinas;
    Curso *dir, *esq;
};

// Entrada e inserção de dados
void InsereDadosCursos(Curso **raizArvCurso) {
    NovoCurso(&(*raizArvCurso), "Seila", 5, 15);
    NovoCurso(&(*raizArvCurso), "bacana", 3, 15);
    NovoCurso(&(*raizArvCurso), "manero", 2, 15);
    NovoCurso(&(*raizArvCurso), "topzera", 5, 15);
    NovoCurso(&(*raizArvCurso), "fera", 4, 15);
    NovoCurso(&(*raizArvCurso), "oskei", 5, 15);
}

void NovoCurso(Curso **raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc) {
    Curso* NovoCurso = (Curso *) malloc(sizeof(Curso));

    NovoCurso->cod_curso = GeraCodCurso(*raizArvCurso);
    strcpy(NovoCurso->nome_curso, NomeCurso);
    NovoCurso->quant_blocos = QuantBlocos;
    NovoCurso->num_sem_disc = NumSemnDisc;
    NovoCurso->arv_disciplinas = NULL;
    InsereDadosDisc(&(NovoCurso->arv_disciplinas), NovoCurso->quant_blocos, NovoCurso->num_sem_disc);
    NovoCurso->dir = NULL;
    NovoCurso->esq = NULL;
    InsereCurso(&(*raizArvCurso), NovoCurso);
}

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

int CursoFolha(Curso *raizArvCurso) {
    int EhFolha = 0;
    if (raizArvCurso->esq == NULL && raizArvCurso->dir == NULL) {
        EhFolha = 1;
    }

    return (EhFolha);
}

int CursoDoisFilhos(Curso *raizArvCurso) {
    int DoisFilhos = 0;
    if (raizArvCurso->esq != NULL && raizArvCurso->dir != NULL) {
        DoisFilhos = 1;
    }

    return (DoisFilhos);
}

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

Curso* MaiorCursoEsq(Curso *raizArvCurso) {
    if (raizArvCurso->dir != NULL) {
        return MaiorCursoEsq(raizArvCurso->dir);
    }
    else {
        return raizArvCurso;
    }
}

Curso* CursoLado(Curso *raizArvCurso) {
    if (raizArvCurso->esq != NULL) {
        return (raizArvCurso->esq);
    }
    else {
        return (raizArvCurso->dir);
    }
}

void RemoveCurso(Curso **raizArvCurso, int CodCurso, char *situacao) {
    if ((*raizArvCurso) != NULL) {
        Curso *Aux, *Filho;

        if ((*raizArvCurso)->cod_curso == CodCurso) {
            if ((*raizArvCurso)->arv_disciplinas != NULL) {
                strcpy(situacao, "Falha na operacao! Curso possui disciplinas cadastradas!");    
            }
            else {
                if (CursoFolha(*raizArvCurso)) {
                    Aux = (*raizArvCurso);
                    (*raizArvCurso) = NULL;
                }
                else if (CursoDoisFilhos(*raizArvCurso)) {
                    Filho = MaiorCursoEsq(*raizArvCurso);
                    Aux = (*raizArvCurso);
                    Filho->dir = (*raizArvCurso)->dir;
                    (*raizArvCurso) = (*raizArvCurso)->esq;
                }
                else {
                    Filho = CursoLado(*raizArvCurso);
                    Aux = (*raizArvCurso);
                    (*raizArvCurso) = Filho;
                }
                free(Aux);
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
    
    if (strlen(situacao) == 0) {
        if (strlen(situacao) == 0) {
        strcpy(situacao, "Falha na operacao! Curso nao encontrada"); 
    }
    }
}