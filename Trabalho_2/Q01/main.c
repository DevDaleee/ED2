#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "impLLRB.h"

int main() {
    ArvRN *RaizArv;
    RaizArv = NULL;
    clock_t start_t, end_t;
    double total_t;

    FILE *file;
    file = fopen("../palavras.txt", "r");

    if (file == NULL) {
        printf("Erro ao Abrir o Arquivo! \n");
        return 0;
    }

    char palavra[100];  
    int repetidas = 1;

    while(fscanf(file, "%s", palavra) != EOF){
        inserir(&RaizArv, palavra, repetidas);
        repetidas++;
    }
    repetidas = 0;
    fclose(file);


    FILE *arqv;
    arqv = fopen("../teste.txt", "r");
    if(arqv == NULL){
        printf("Erro ao Abrir o Arquivo! \n");
        return 0;
    }

    char palavra2[100];
    while(fscanf(arqv, "%s", palavra2) != EOF){
        start_t = clock();
        BuscarPalavra(RaizArv, palavra2);
        end_t = clock();
        total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
        printf(" %s : %lf\n", palavra2, total_t);
    }

    printf("\n");
    return 0;
}
    