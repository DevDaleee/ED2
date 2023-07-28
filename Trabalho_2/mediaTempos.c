#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    file = fopen("../TemposInsercaoDecrescente.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    double tempos = 0;
    double valor;
    int repetidas = 0;

    while (fscanf(file, "%lf", &valor) == 1) {
        tempos += valor;
        repetidas++;
    }

    if (repetidas > 0) {
        double media = tempos / repetidas;
        printf("Média dos tempos: %lf\n", media);
    } else {
        printf("O arquivo está vazio ou não contém números válidos.\n");
    }

    fclose(file);
    return 0;
}
