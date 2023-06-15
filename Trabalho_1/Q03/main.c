#include <stdio.h>
#include <stdlib.h>
#include "ImpCurso.h"
#include "ImpDisciplinas.h"

void menu(){
    printf("\n-------------------------------------\n");
    printf("\t\tMENU\n");
    printf("[1] - Imprimir Cursos.\n");
    printf("[2] - Imprimir Dados Do Curso.\n");
    printf("[3] - Imprimir Cursos Com a Mesma Quantidade de Blocos.\n");
    printf("[4] - Imprimir Disciplinas de um Curso.\n");
    printf("[5] - Imprimir Dados de uma Disciplina.\n");
    printf("[6] - Imprimir Disciplinas de um Determinado Bloco de um Curso.\n");
    printf("[7] - Imprimir as Disciplinas de um Determinado Curso com a Mesma Carga Horária.\n");
    printf("[8] - Excluir Disciplina.\n");
    printf("[9] - Excluir Curso.\n");
    printf("[0] - Finalizar Operação.\n");
    printf("-------------------------------------\n");
}

int main()
{
    Cursos *raizArvCurso;
    raizArvCurso = NULL;

    int op=1, cod_curso, num_blocos, cod_disc, bloco, carga_h, removido;
    InsereDadosCursos(&(*raizArvCurso));

    while (op!=0){
        menu();
        printf("\nEscolha uma opção: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1: //Imprimir a árvore de cursos em ordem crescente pelo código do curso
            printf("\nÁrvore de Cursos: \n");
            ImprimeArvCursos(raizArvCurso);
            break;

        case 2: //Imprimir os dados de um curso dado o código do mesmo;
            printf("\nCódigo do Curso: ");
            scanf("%d", &cod_curso);
            printf("Árvore de Disciplinas: \n");
            ImprimeDisciplinasCurso(raizArvCurso, cod_curso);
            break;
        
        case 3://Imprimir todos os cursos com a mesma quantidade de blocos, onde o usuário informe a
        //quantidade de blocos;
            printf("\nQuantidade de Blocos: ");
            scanf("%d", &num_blocos);
            ImprimeCursosBlocosIguais(raizArvCurso, num_blocos);
            break;
        
        case 4://Imprimir a árvore de disciplinas em ordem crescente pelo código das disciplinas dado
        //o código do curso;
            printf("\nCódigo do Curso: ");
            scanf("%d", &cod_curso);
            printf("Árvore de Disciplinas:\n");
            ImprimeDisciplinasCurso(raizArvCurso, cod_curso);
            break;
        
        case 5://Imprimir os dados de uma disciplina dado o código dela e do curso ao qual ela pertence;
            printf("\nCódigo da Disciplina: ");
            scanf("%d", &cod_disc);
            printf("Disciplinas do Curso: %d\n", cod_disc);
            ImprimeDisciplinaCurso(raizArvCurso, cod_curso, cod_disc);
            break;
        
        case 6://Imprimir as disciplinas de um determinado bloco de um curso, dado o bloco e o código do curso;
            printf("\nCódigo do Curso: ");
            scanf("%d", &cod_curso);
            if (BuscaCursoCod(raizArvCurso, cod_curso) == NULL) {
                printf("Curso não encontrado!\n");
            } else {
                printf("Disciplinas do mesmo bloco:\n");
                printf("Bloco: ");
                scanf("%d", &bloco);
                ImprimeDisciplinaBloco(raizArvCurso, bloco);
            }
            break;
        
        case 7://Imprimir todas as disciplinas de um determinado curso com a mesma carga horária, onde o código
        //do curso e a carga horária devem ser informadas pelo usuário;
            printf("\nCódigo do Curso: ");
            scanf("%d", &cod_curso);
            printf("Carga Horaria: ");
            scanf("%d", &carga_h);
            ImprimeDisciplinasCargaHoraria(raizArvCurso, cod_curso, carga_h);
            break;
        
        case 8://Excluir uma disciplina dado o código da disciplina e o código do curso;
            printf("\nCódigo do Curso: ");
            scanf("%d", &cod_curso);
            ImprimeDisciplinasCurso(raizArvCurso, cod_curso);
            printf("Código da Disciplina: ");
            scanf("%d", &cod_disc);
            if( raizArvCurso != NULL ){
                RemoveDisciplinas(raizArvCurso, cod_curso, cod_disc);
                printf("Disciplina removida com sucesso!\n");
                ImprimeDisciplinasCurso(raizArvCurso, cod_curso);
            }else{
                printf("Árvore de Cursos Vazia!\n");
                printf("Portanto não foi possivel remover!\n");
            }

            break;
        
        case 9://Excluir um curso dado o código do mesmo, desde que não tenha nenhuma disciplina cadastrada
        //para aquele curso.
            printf("\nCódigo do Curso: ");
            scanf("%d", &cod_curso);
            removido = 1;
            removido = RemoveCurso(raizArvCurso, cod_curso);
            if(removido == 1){
                printf("Curso removido com sucesso!\n");
                ImprimeArvCursos(raizArvCurso); 
            }
            break;

        case 0:
            printf("\nOperação Finalizada!\n\n");
            break;

        default:
            printf("\nERRO: Opção Invallida!\n");
            break;
        }
    }

    return 0;
}