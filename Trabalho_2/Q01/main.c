#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "impLLRB.h"

int main() {
    ArvRN *RaizArv;
    RaizArv = NULL;

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
    ImprimeArvoreInOrdemLLRB(RaizArv);
    ImprimirListaLinhas(RaizArv);
    printf("\n");
    return 0;
}
    