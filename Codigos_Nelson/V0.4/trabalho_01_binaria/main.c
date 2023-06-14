#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "curso.h"

void Menu();
void ResetaSituacao(char *situacao);

void Op1(Curso *raizArvCurso, char *situacao);
void Op2(Curso *raizArvCurso, char *situacao);
void Op3(Curso *raizArvCurso, char *situacao);
void Op4(Curso *raizArvCurso, char *situacao);
void Op5(Curso *raizArvCurso, char *situacao);
void Op6(Curso *raizArvCurso, char *situacao);
void Op7(Curso *raizArvCurso, char *situacao);
void Op8(Curso *raizArvCurso, char *situacao);
void Op9(Curso *raizArvCurso, char *situacao);


int main() {
    Curso *raizArvCurso;
    raizArvCurso = NULL;
    InsereDadosCursos(&raizArvCurso);

    int op = 0;
    char situacao[30] = "";

    do { 
        Menu();
        printf("Digite sua opcao: ");
        scanf("%d", &op);

        switch (op)
        {

        case 0:
            puts("Finalizando programa...");
            break;
        case 1:
            Op1(raizArvCurso, situacao);
            printf("%s\n", situacao);
            break;
        
        case 2:
            Op2(raizArvCurso, situacao);
            printf("%s\n", situacao);
            break;

        case 3:
            Op3(raizArvCurso, situacao);
            printf("%s\n", situacao);
            break;

        case 4:
            Op4(raizArvCurso, situacao);
            printf("%s\n", situacao);
            break;

        case 5:
            Op5(raizArvCurso, situacao);
            printf("%s\n", situacao);
            break;

        case 6:
            Op6(raizArvCurso, situacao);
            printf("%s\n", situacao);
            break;

        case 7:
            Op7(raizArvCurso, situacao);
            printf("%s\n", situacao);
            break;

        case 8:
            Op8(raizArvCurso, situacao);
            printf("%s\n", situacao);
            break;
        
        case 9:
            Op9(raizArvCurso, situacao);
            printf("%s\n", situacao);
            break;

        default:
            puts("Opcao invalida!");
            break;
        }

        ResetaSituacao(situacao);
    } while (op != 0);


    return 0;
}

void Menu() {
    puts("-------------------------------------");
    puts("[1] - Imprimir arvore de cursos;");
    puts("[2] - Imprimir dados de um curso;");
    puts("[3] - Imprimir cursos com a mesma quantidade de blocos;");
    puts("[4] - Imprimir arvore de disciplinas;");
    puts("[5] - Imprimir dados de uma disciplina;");
    puts("[6] - Imprimir disciplinas de um bloco;");
    puts("[7] - Imprimir disciplinas com mesma carga horaria;");
    puts("[8] - Excluir disciplina;");
    puts("[9] - Excluir curso;");
    puts("[0] - Finalizar o programa;");
    puts("-------------------------------------");
}

void ResetaSituacao(char *situacao) {
    strcpy(situacao, "");
}

void Op1(Curso *raizArvCurso, char *situacao) {
    ImprimeArvCursos(raizArvCurso, situacao);
    puts("-------------------------------------");
}

void Op2(Curso *raizArvCurso, char *situacao){ 
    int CodCurso;

    printf("Digite o codigo do curso: ");
    scanf("%d", &CodCurso);
    puts("-------------------------------------");

    ImprimeCurso(raizArvCurso, CodCurso, situacao);
}

void Op3(Curso *raizArvCurso, char *situacao) {
    int QuantBlocos;

    printf("Digite a quantidade de blocos: ");
    scanf("%d", &QuantBlocos);
    puts("-------------------------------------");

    ImprimeCursosQuantBlocosIguais(raizArvCurso, QuantBlocos, situacao);
}

void Op4(Curso *raizArvCurso, char *situacao) {
    int CodCurso;
    printf("Digite o codigo do curso: ");
    scanf("%d", &CodCurso);
    puts("-------------------------------------");

    ImprimeDisciplinasCurso(raizArvCurso, CodCurso, situacao);
}

void Op5(Curso *raizArvCurso, char *situacao) {
    int CodCurso, CodDisc;
    printf("Digite o codigo do curso: ");
    scanf("%d", &CodCurso);
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &CodDisc);
    puts("-------------------------------------");

    ImprimeDisciplinaCurso(raizArvCurso, CodCurso, CodDisc, situacao);
}

void Op6(Curso *raizArvCurso, char *situacao){
    int CodCurso, Bloco;

    printf("Digite o codigo do curso: ");
    scanf("%d", &CodCurso);
    printf("Digite o bloco: ");
    scanf("%d", &Bloco);
    puts("-------------------------------------");

    ImprimeDiscMesmoBloco(raizArvCurso, CodCurso, Bloco, situacao);
}

void Op7(Curso *raizArvCurso, char *situacao) {
    int CodCurso, CargaHoraria;

    printf("Digite o codigo do curso: ");
    scanf("%d", &CodCurso);
    printf("Carga horaria: ");
    scanf("%d", &CargaHoraria);
    puts("-------------------------------------");

    ImprimeDiscMesmaCH(raizArvCurso, CodCurso, CargaHoraria, situacao);
}

void Op8(Curso *raizArvCurso, char *situacao) {
    int CodCurso, CodDisc;
    printf("Digite o codigo do curso: ");
    scanf("%d", &CodCurso);
    printf("Digite o codigo da disciplina: ");
    scanf("%d", &CodDisc);
    puts("-------------------------------------");

    RemoveDiscCurso(raizArvCurso, CodCurso, CodDisc, situacao);
}

void Op9(Curso *raizArvCurso, char *situacao) {
    int CodCurso;
    printf("Digite o codigo do curso: ");
    scanf("%d", &CodCurso);
    puts("-------------------------------------");
    RemoveCurso(&(raizArvCurso), CodCurso, situacao);    
}