#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ImpCurso.h"

void ArmazenaTemposInsercao(double TempoInsercao);
void ArmazenaTemposBusca(double TempoBusca);
void TesteInsercao(Cursos **raizArvCurso, double *TempoInsercao, int *maior);
void TesteBusca(Cursos *raizArvCurso, double *TempoBusca, int CodCursoBusca);

int main() {
    Cursos *raizArvCurso;
    raizArvCurso = NULL;

    double TempoInsercao;
    double TempoBusca;
    int maior;
    TesteInsercao(&raizArvCurso, &TempoInsercao, &maior);
    printf("%d\n", maior);
    TesteBusca(raizArvCurso, &TempoBusca, maior);
}

void ArmazenaTemposInsercao(double TempoInsercao) {
    FILE *arquivo;

    //arquivo = fopen("dados/TemposInsercaoCrescente.txt", "a");
    //arquivo = fopen("dados/TemposInsercaoAleatorio.txt", "a");
    arquivo = fopen("dados/TemposInsercaoDecrescente.txt", "a");

    if (arquivo == NULL) {
        puts("OPS");
        return;
    }

    fprintf(arquivo, "%f\n", TempoInsercao);

    fclose(arquivo);
}

void ArmazenaTemposBusca(double TempoBusca) {
    FILE *arquivo;

    //arquivo = fopen("dados/TemposBuscaCrescente.txt", "a");
    //arquivo = fopen("dados/TemposBuscaAleatorio.txt", "a");
    arquivo = fopen("dados/TemposBuscaDecrescente.txt", "a");

    if (arquivo == NULL) {
        puts("OPS");
        return;
    }

    fprintf(arquivo, "%3f\n", TempoBusca);

    fclose(arquivo);
}

void TesteInsercao(Cursos **raizArvCurso, double *TempoInsercao, int *maior) {
    int quant = 39700;
    FILE *ArqDadosDecresc;
    int numero;

    ArqDadosDecresc = fopen("dados/DadosDecrescente.txt", "r");
    if (ArqDadosDecresc == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    int cont = 0;
    while (fscanf(ArqDadosDecresc, "%d,", &numero) != EOF && cont < quant) {
        if (cont == 0) {
            *maior = numero;
        } else if (numero > *maior) {
            *maior = numero;
        }

        Cursos *NovoNoCurso = EntradaDadosCurso(raizArvCurso, "teste", 8, 15, numero);
        InsereCurso(raizArvCurso, NovoNoCurso);

        cont++;
    }

    quant = cont + 30;
    clock_t inicio, fim;
    int valorMaisProf = 300;

    for (int i = 0; i < 30; i++) {
        valorMaisProf -= 10;
        Cursos *NovoNoCurso = EntradaDadosCurso(raizArvCurso, "teste", 8, 15, valorMaisProf);
        printf("%d\n", valorMaisProf);
        inicio = clock();
        InsereCurso(raizArvCurso, NovoNoCurso);
        fim = clock();

        *TempoInsercao = (double)(fim - inicio) / CLOCKS_PER_SEC;
        *TempoInsercao = *TempoInsercao * 1000;

        ArmazenaTemposInsercao(*TempoInsercao);
    }

    *maior = valorMaisProf;
    fclose(ArqDadosDecresc);
}


void TesteBusca(Cursos *raizArvCurso, double *TempoBusca, int CodCursoBusca){
    clock_t inicio, fim;
    Cursos *teste;

    for (int i = 0; i < 30; i++) {
        inicio = clock();
        teste = BuscaCursoCod(raizArvCurso, CodCursoBusca);
        fim = clock();
        *TempoBusca = (double)(fim - inicio) / CLOCKS_PER_SEC;
        *TempoBusca = *TempoBusca * 1000;
        ArmazenaTemposBusca(*TempoBusca);
    }
}