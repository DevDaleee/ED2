#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *file;
    file = fopen("../string.txt", "r");

    if(file == NULL){
        printf("Falha ao abrir o arquivo! \n");
        return 0;
    }
    char frase[100];

    while(fgets(frase, 100, file) != NULL){
        printf("%s", frase);
    }
    fclose(file);
    printf("\n");
    return 0;
}