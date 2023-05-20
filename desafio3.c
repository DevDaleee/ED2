#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void concatena_strings(char **destino, const char *origem) {
    if (destino == NULL || origem == NULL) {
        return;
    }

    int tamanho_destino = strlen(*destino);
    int tamanho_origem = strlen(origem);
    int tamanho_total = tamanho_destino + tamanho_origem + 1; 
    char *nova_string = (char*)malloc(tamanho_total * sizeof(char));

    strcpy(nova_string, *destino);

    strcat(nova_string, origem);

    free(*destino);

    *destino = nova_string;
}

int main() {
    char *string_destino = (char*)malloc(20 * sizeof(char));
    strcpy(string_destino, "Hello");

    const char *string_origem = " World!";

    printf("Antes da concatenação: %s\n", string_destino);

    concatena_strings(&string_destino, string_origem);

    printf("Após a concatenação: %s\n", string_destino);

    free(string_destino);

    return 0;
}