#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "ImpCurso.h"
#include "ImpDisciplinas.h"

struct cursos {
    int cod_curso;
    char nome_curso[40];
    int quant_blocos;
    int num_sem_disc;
    Disciplinas *arv_disciplinas;
    Cursos *dir, *esq;
};


void InsereDadosCursos(Cursos **raizArvCurso) {
    EntradaDadosCurso(&(*raizArvCurso), "Seila", 5, 15);
    EntradaDadosCurso(&(*raizArvCurso), "bacana", 3, 15);
    EntradaDadosCurso(&(*raizArvCurso), "manero", 2, 15);
    EntradaDadosCurso(&(*raizArvCurso), "topzera", 5, 15);
    EntradaDadosCurso(&(*raizArvCurso), "fera", 4, 15);
    EntradaDadosCurso(&(*raizArvCurso), "oskey", 5, 15);
}

void EntradaDadosCurso(Cursos **raizArvCurso, char *NomeCurso, int QuantBlocos, int NumSemnDisc) {
    Cursos* NovoCurso = (Cursos *) malloc(sizeof(Cursos));

    NovoCurso->cod_curso = GeraCodCurso(*raizArvCurso);
    strcpy(NovoCurso->nome_curso, NomeCurso);
    NovoCurso->quant_blocos = QuantBlocos;
    NovoCurso->num_sem_disc = NumSemnDisc;
    NovoCurso->arv_disciplinas = NULL;
    //InsereDadosDisc(&(NovoCurso->arv_disciplinas));
    NovoCurso->dir = NULL;
    NovoCurso->esq = NULL;
    InsereCurso(&(*raizArvCurso), NovoCurso);
}

void InsereCurso(Cursos **raizArvCurso, Cursos *NovoCurso) {
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

int GeraCodCurso(Cursos *raizArvCurso) {
    int CodUnicoCurso;
    do
    {
        CodUnicoCurso = rand() % 1000;
    } while (BuscaCursoCod(raizArvCurso, CodUnicoCurso) != NULL);
    return (CodUnicoCurso);
}

Cursos *BuscaCursoCod(Cursos *raizArvCurso, int CodCurso) {
    Cursos* Encontrou;
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
void ImprimeArvCursos(Cursos *raizArvCurso) {
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

void ImprimeDisciplinasCurso(Cursos *raizArvCurso, int CodCurso) {
    Cursos *AuxCurso;
    if ((AuxCurso = (BuscaCursoCod(raizArvCurso, CodCurso))) != NULL) {
        ImprimeArvDisc(AuxCurso->arv_disciplinas);
    }
    else {
        puts("Curso nao encontrado!!!");
    }    
}

void ImprimeCurso(Cursos *raizArvCurso, int CodCurso) {
    Cursos *AuxCurso;

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

void ImprimeCursosBlocosIguais(Cursos *raizArvCurso, int NumBlocos) {
    if (raizArvCurso != NULL) {
        if (raizArvCurso->quant_blocos == NumBlocos) {
            printf("---------------------\n");
            printf("Curso - %s\n", raizArvCurso->nome_curso);
            printf("Num de blocos: %d\n", raizArvCurso->quant_blocos);
            printf("---------------------\n");
        }
        ImprimeCursosBlocosIguais(raizArvCurso->esq, NumBlocos);
        ImprimeCursosBlocosIguais(raizArvCurso->dir, NumBlocos);

    }
}

void ImprimeDisciplinaCurso(Cursos *raizArvCurso, int CodCurso, int CodDisc) {
    Cursos *AuxCurso;
    if (raizArvCurso != NULL) {
        if ((AuxCurso = BuscaCursoCod(raizArvCurso, CodCurso)) != NULL) {
            Disciplinas *AuxDisciplina;
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


void ImprimeDisciplinaBloco(Cursos *raizArvCurso, int bloco){
    if(raizArvCurso != NULL){
        ImprimeDiscMsmBloco(raizArvCurso->arv_disciplinas, bloco);
    }else{
        puts("Nenhum curso na arvore!");
    }
}

void ImprimeDisciplinasCargaHoraria(Cursos *raizArvCurso, int cod_curso, int ch){
    if(raizArvCurso != NULL){
        if(BuscaCursoCod(raizArvCurso, cod_curso) != NULL){
            ImprimeDiscCargaHoraria(raizArvCurso->arv_disciplinas, ch);
        }else{
            puts("Curso nao encontrado!");
        }
    }else{
        puts("Nenhum curso na arvore!");
    }
}


void RemoveDisciplinas(Cursos* raizArvCurso, int cod_curso, int cod_disc) {
    if (raizArvCurso != NULL) {
        Cursos* encontrou = BuscaCursoCod(raizArvCurso, cod_curso);
        if (encontrou != NULL && encontrou->cod_curso == cod_curso) {
            raizArvCurso->arv_disciplinas = RemoveDisc(encontrou->arv_disciplinas, cod_disc);
        } else {
            puts("Curso nao encontrado!");
        }
    } else {
        puts("Nenhum curso na arvore!");
    }
}

int RemoveCurso(Cursos *raizArvCursos, int cod_curso){
    int removido = 0;
    if(raizArvCursos != NULL){
        if(raizArvCursos->arv_disciplinas != NULL){
            printf("Curso Ainda tem Disciplinas!\n");
            printf("Remova-as primeiro!\n");
        }else{
            RemoveCursoDaArv(raizArvCursos, cod_curso);
            removido = 1;
        }
    }
    return removido;
}

void RemoveCursoDaArv(Cursos *raizArvCursos, int cod_curso) {
    Cursos* raiz = raizArvCursos;
    Cursos* filho = NULL;
    Cursos* atual = raiz;

    // Find the node to be removed and its filho
    while (atual != NULL && atual->cod_curso != cod_curso) {
        filho = atual;
        if (cod_curso < atual->cod_curso) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    // Node not found
    if (atual == NULL) {
        return;
    }

    // Node has no children
    if (atual->esq == NULL && atual->dir == NULL) {
        if (filho == NULL) {
            raizArvCursos = NULL;
        } else if (filho->esq == atual) {
            filho->esq = NULL;
        } else {
            filho->dir = NULL;
        }
        free(atual);
    }
    // Node has one child
    else if (atual->esq == NULL || atual->dir == NULL) {
        Cursos* child = (atual->esq != NULL) ? atual->esq : atual->dir;
        if (filho == NULL) {
            raizArvCursos = child;
        } else if (filho->esq == atual) {
            filho->esq = child;
        } else {
            filho->dir = child;
        }
        free(atual);
    }
    // Node has two children
    else {
        Cursos* new = atual;
        Cursos* aux2 = atual->dir;

        while (aux2->esq != NULL) {
            new = aux2;
            aux2 = aux2->esq;
        }

        if (new != atual) {
            new->esq = aux2->dir;
        } else {
            new->dir = aux2->dir;
        }

        atual->cod_curso = aux2->cod_curso;
        free(aux2);
    }
}