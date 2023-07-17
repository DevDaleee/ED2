#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "curso.h"

void ArmazenaTemposInsercao(double TempoInsercao);
void ArmazenaTemposBusca(double TempoBusca);
void TesteInsercao(Curso **raizArvCurso, double *TempoInsercao, int *maior);
void TesteBusca(Curso *raizArvCurso, double *TempoBusca, int CodCursoBusca);

int main() {
    Curso *raizArvCurso;
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

void TesteInsercao(Curso **raizArvCurso, double *TempoInsercao, int *maior) {
    int quant = 39700;
    //FILE *ArqDadosCresc;
    //FILE *ArqDadosAleatorios;
    FILE *ArqDadosDecresc;
    int numero;

    //ArqDadosCresc = fopen("dados/DadosCrescente.txt", "r");
    //ArqDadosAleatorios = fopen("dados/DadosAleatorios.txt", "r");
    ArqDadosDecresc = fopen("dados/DadosDecrescente.txt", "r");

    int cont = 0;
    while (fscanf(ArqDadosDecresc, "%d", &numero) != EOF && cont < quant) {

        // Pula a vírgula
        fseek(ArqDadosDecresc, 1, SEEK_CUR);
        if (cont == 0) {
            *maior = numero;
        }
        else if (numero > *maior) *maior = numero;

        Curso *NovoNoCurso = NovoCurso(*raizArvCurso, "teste", 8, 15, numero);
        InsereCurso(raizArvCurso, NovoNoCurso);

        cont++;
    
    }
    
    quant = cont + 30;
    clock_t inicio, fim;

    //int valorMaisProf = BuscaValorNoMaisProf(*raizArvCurso);
    int valorMaisProf = 300;
    for (int i = 0; i < 30; i++) {
        valorMaisProf -= 10;
        Curso *NovoNoCurso = NovoCurso(*raizArvCurso, "teste", 8, 15, valorMaisProf);
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

void TesteBusca(Curso *raizArvCurso, double *TempoBusca, int CodCursoBusca){
    clock_t inicio, fim;
    Curso *teste;

    for (int i = 0; i < 30; i++) {
        inicio = clock();
        teste = BuscaCursoCod(raizArvCurso, CodCursoBusca);
        fim = clock();
        *TempoBusca = (double)(fim - inicio) / CLOCKS_PER_SEC;
        *TempoBusca = *TempoBusca * 1000;
        ArmazenaTemposBusca(*TempoBusca);
    }
}