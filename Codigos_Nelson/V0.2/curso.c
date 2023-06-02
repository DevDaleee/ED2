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
    EntradaDadosCurso(&(*raizArvCurso), "Seila", 5, 15);
    EntradaDadosCurso(&(*raizArvCurso), "bacana", 3, 15);
    EntradaDadosCurso(&(*raizArvCurso), "manero", 2, 15);
    EntradaDadosCurso(&(*raizArvCurso), "topzera", 5, 15);
    EntradaDadosCurso(&(*raizArvCurso), "fera", 4, 15);
    EntradaDadosCurso(&(*raizArvCurso), "oskei", 5, 15);
}

void EntradaDadosCurso(Curso **raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc) {
    Curso* NovoCurso = (Curso *) malloc(sizeof(Curso));

    NovoCurso->cod_curso = GeraCodCurso(*raizArvCurso);
    strcpy(NovoCurso->nome_curso, NomeCurso);
    NovoCurso->quant_blocos = QuantBlocos;
    NovoCurso->num_sem_disc = NumSemnDisc;
    NovoCurso->arv_disciplinas = NULL;
    InsereDadosDisc(&(NovoCurso->arv_disciplinas));
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

//Impressão de dados
void ImprimeArvCursos(Curso *raizArvCurso) {
    if (raizArvCurso != NULL) {
        ImprimeArvCursos(raizArvCurso->esq);
        printf("Codigo do curso: %d\n", raizArvCurso->cod_curso);
        printf("Nome do curso: %s\n", raizArvCurso->nome_curso);
        printf("Numero de blocos: %d\n", raizArvCurso->quant_blocos);
        printf("Numero de semanas para cada disciplina: %d\n", raizArvCurso->num_sem_disc);
        puts("");
        ImprimeArvCursos(raizArvCurso->dir);
    }
}

void ImprimeDisciplinasCurso(Curso *raizArvCurso, int CodCurso) {
    Curso *AuxCurso;
    if ((AuxCurso = (BuscaCursoCod(raizArvCurso, CodCurso))) != NULL) {
        ImprimeArvDisc(AuxCurso->arv_disciplinas);
    }
    else {
        puts("Curso nao encontrado!!!");
    }    
}

void ImprimeCurso(Curso *raizArvCurso, int CodCurso) {
    Curso *AuxCurso;

    if ((AuxCurso = BuscaCursoCod(raizArvCurso, CodCurso)) != NULL) {
        printf("Curso - %s\n", AuxCurso->nome_curso);
        printf("Codigo: %d\n", AuxCurso->cod_curso);
        printf("Numero de blocos: %d\n", AuxCurso->quant_blocos);
        printf("Numero de semanas para cada disciplina: %d\n", AuxCurso->num_sem_disc);
        puts("");
    }
    else {
        puts("Curso nao encontrado!!!");
    }
}

void ImprimeCursosBlocosIguais(Curso *raizArvCurso, int NumBlocos) {
    if (raizArvCurso != NULL) {
        if (raizArvCurso->quant_blocos == NumBlocos) {
            printf("Curso - %s\n", raizArvCurso->nome_curso);
            printf("Num de blocos: %d\n", raizArvCurso->quant_blocos);
        }
        ImprimeCursosBlocosIguais(raizArvCurso->esq, NumBlocos);
        ImprimeCursosBlocosIguais(raizArvCurso->dir, NumBlocos);

    }
}

void ImprimeDisciplinaCurso(Curso *raizArvCurso, int CodCurso, int CodDisc) {
    Curso *AuxCurso;
    if (raizArvCurso != NULL) {
        if ((AuxCurso = BuscaCursoCod(raizArvCurso, CodCurso)) != NULL) {
            Disciplina *AuxDisciplina;
            if ((AuxDisciplina = BuscaDiscCod(AuxCurso->arv_disciplinas, CodDisc)) != NULL) {
                ImprimeDisc(AuxDisciplina);
            }
            else {
                puts("Disciplina nao encontrada!");
            }
        }
        else {
            puts("Curso nao encontrado!");
        }
    }
    else {
        puts("Nenhum curso na arvore!");
    }
}