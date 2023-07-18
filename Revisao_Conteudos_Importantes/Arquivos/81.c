#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *file;
    file = fopen("../string.txt", "w");
    fprintf(file, "Como é amigo?");
    fclose(file);


    return 0;
}