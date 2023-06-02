#include <stdio.h>
#include <stdlib.h>
#include "curso.h"

int main() {
    Curso *raizArvCurso;
    raizArvCurso = NULL;

    InsereDadosCursos(&(raizArvCurso));
    ImprimeArvCursos(raizArvCurso);

    int cod_curso;
    printf("Cod Curso: ");
    scanf("%d", &cod_curso);
    ImprimeDisciplinasCurso(raizArvCurso, cod_curso);
    int cod_disc;
    printf("Cod disciplina: ");
    scanf("%d", &cod_disc);
    ImprimeDisciplinaCurso(raizArvCurso, cod_curso, cod_disc);


    return 0;
}