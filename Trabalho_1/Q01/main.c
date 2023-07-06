#include <stdio.h>
#include <stdlib.h>
#include "ImpCurso.h"
#include "ImpDisciplinas.h"

int main() {
    Cursos *raizArvCurso;
    raizArvCurso = NULL;

    //A e B
    InsereDadosCursos(&(raizArvCurso));

    //C - 1 - ABB 
    printf("Árvore de Cursos \n");
    ImprimeArvCursos(raizArvCurso);

    //C - 2 / 4 - ABB
    int cod_curso;
    printf("Cod Curso: ");
    scanf("%d", &cod_curso);
    printf("Árvore de Disciplinas\n");
    ImprimeDisciplinasCurso(raizArvCurso, cod_curso);

    //C - 3 - ABB
    int NumBlocos;
    printf("Para imprimir os cursos com a mesma quanitdade de blocos, digite a quantidade de blocos: \n");
    scanf("%d", &NumBlocos);
    ImprimeCursosBlocosIguais(raizArvCurso, NumBlocos);

    //C - 5 - ABB
    int cod_disc;
    printf("Cod disciplina: ");
    scanf("%d", &cod_disc);
    printf("Disciplinas do curso: %d\n", cod_disc);
    ImprimeDisciplinaCurso(raizArvCurso, cod_curso, cod_disc);


    //C - 6 - ABB
    printf("Qual Curso Deseja Procurar as Disciplinas do Mesmo Bloco?\n");
    scanf("%d", &cod_curso);
    if (BuscaCursoCod(raizArvCurso, cod_curso) == NULL) {
        printf("Curso não encontrado!\n");
    } else {
        int bloco;
        printf("Disciplinas do mesmo bloco:\n");
        printf("Bloco: ");
        scanf("%d", &bloco);
        ImprimeDisciplinaBloco(raizArvCurso, bloco);
    }

    //1 - C - 7
    //Imprimir todas as disciplinas a mesma carga horária, 
    //Código do curso e a carga horária devem ser informadas pelo usuário;  
    int ch;
    printf("Cod curso: ");
    scanf("%d", &cod_curso);
    printf("Carga horaria: ");
    scanf("%d", &ch);
    ImprimeDisciplinasCargaHoraria(raizArvCurso, cod_curso, ch);


    //1 - C - 8
    printf("Cod curso: ");
    scanf("%d", &cod_curso);
    ImprimeDisciplinasCurso(raizArvCurso, cod_curso);
    printf("Cod Disciplina: ");
    scanf("%d", &cod_disc);
    if( raizArvCurso != NULL ){
        RemoveDisciplinas(raizArvCurso, cod_curso, cod_disc);
        printf("Disciplina removida com sucesso!\n\n\n");
        ImprimeDisciplinasCurso(raizArvCurso, cod_curso);
    }else{
        printf("Árvore de Cursos Vazia!\n");
        printf("Portanto nao foi possivel remover!\n");
    }

    //1 - C - 9
    printf("Cod curso: ");
    scanf("%d", &cod_curso);
    int removido = 1;
    removido = RemoveCurso(raizArvCurso, cod_curso);
    if(removido == 1){
        printf("Curso removido com sucesso!\n");
        ImprimeArvCursos(raizArvCurso); 
    }

    return 0;
}