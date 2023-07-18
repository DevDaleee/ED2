#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *file;
    file = fopen("../numero.txt", "r");

    if(file == NULL){
        printf("Falha ao abrir o arquivo!\n");
        return 0;
    }

    int x, y, z;
    fscanf(file, "%i %i %i", &x, &y, &z);
    printf("%i %i %i\n", x, y, z);

    fclose(file);

    return 0;
}