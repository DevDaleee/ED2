#include <stdio.h>

void multiplica_por_referencia(int *valor, int multiplicador) {
    *valor *= multiplicador;
}

int main() {
    int numero = 5;
    int multiplicador = 3;

    printf("Antes da multiplicação: numero = %d\n", numero);

    multiplica_por_referencia(&numero, multiplicador);

    printf("Depois da multiplicação: numero = %d\n", numero);

    return 0;
}