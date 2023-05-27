#include <stdio.h>
#include <stdlib.h>
#include "implementacoes.h"

struct curso {
    int codigo;
    char nome_curso[35];
    int qtd_blocos;
    int num_sem; 
    Cursos *esq, *dir;
}Curso;

int GeraCodigo(int *valor){
    srand(time(NULL));
    *valor = 1+(rand()%1000);
}

Cursos *CriaCurso(Cursos *curso){
    
}
