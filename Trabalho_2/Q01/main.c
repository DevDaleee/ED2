#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "impLLRB.h"

int main() {
    ArvRN *RaizArv;
    RaizArv = NULL;
    FILE *file;
    file = fopen("../teste.txt", "r");
    if (file == NULL) {
        printf("Erro ao Abrir o Arquivo! \n");
        return 0;
    }
    char palavra[100];

    while (fgets(palavra, 100, file) != NULL) {
        palavra[strcspn(palavra, "\n")] = '\0';
        inserir(&RaizArv, palavra);
    }

    fseek(file, 0, SEEK_SET);

    ImprimeArvoreInOrdemLLRB(RaizArv);
    printf("\n");

    return 0;
}
