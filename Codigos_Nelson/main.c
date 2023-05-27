#include <stdio.h>
#include <stdlib.h>
#include "arv_curso.h"

int main() {
    Curso *raizArvCurso;
    raizArvCurso = NULL;

    InsereDadosCursos(&raizArvCurso);
    ImprimeArvCursos(raizArvCurso);

    return 0;
}