#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 42;

    int valor = *ptr;
    printf("Valor: %d\n", valor);

    free(ptr);

    return 0;
}