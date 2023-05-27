#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "arv_curso.h"
#include "arv_disciplina.h"

struct curso {
    int cod_curso;
    char nome_curso[40];
    int quant_blocos;
    int num_sem_disc;
    Disciplina *arv_disciplinas;
    Curso *dir;
    Curso *esq; 
};

void InsereDadosCursos(Curso **raizArvCurso) {
    EntradaDadosCurso(&(*raizArvCurso), "Seila", 5, 15);
    
    EntradaDadosCurso(&(*raizArvCurso), "Seinao", 12, 15);
    EntradaDadosCurso(&(*raizArvCurso), "Curso de burro", 4, 15);
    EntradaDadosCurso(&(*raizArvCurso), "Terror dos otaro", 8, 15);
    EntradaDadosCurso(&(*raizArvCurso), "Boca de badalo", 6, 15);
    EntradaDadosCurso(&(*raizArvCurso), "Boca de suvela", 8, 15);
    EntradaDadosCurso(&(*raizArvCurso), "Dedo do marcos", 10, 15);
}

void EntradaDadosCurso(Curso **raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc) {
    Curso* NovoCurso = (Curso *) malloc(sizeof(Curso));

    NovoCurso->cod_curso = GeraCodUnico((*raizArvCurso));
    strcpy(NovoCurso->nome_curso, NomeCurso);
    NovoCurso->quant_blocos = QuantBlocos;
    NovoCurso->num_sem_disc = NumSemnDisc;
    NovoCurso->arv_disciplinas = NULL;
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

int GeraCodUnico(Curso *raizArvCurso) {
    int CodUnicoCurso;
    do
    {
        CodUnicoCurso = rand() % 1000;
    } while (BuscaCursoCod(raizArvCurso, CodUnicoCurso));

    return (CodUnicoCurso);
}

int BuscaCursoCod(Curso *raizArvCurso, int CodCurso) {
    int Encontrou = 0;
    if (raizArvCurso != NULL) {
        if (raizArvCurso->cod_curso == CodCurso) {
            Encontrou = 1;   
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