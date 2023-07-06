#include <stdio.h>
#include <stdlib.h>
#include "LLrb_Imp.h"


int main(){
    ArvRN *RaizArv;
    RaizArv = NULL;

    inserir(&(RaizArv), 10);
    inserir(&(RaizArv), 20);
    inserir(&(RaizArv), 30);
    inserir(&(RaizArv), 40);

    ImprimeArvore(RaizArv);
    printf("\n");
    remover(&(RaizArv), 40);
    ImprimeArvore(RaizArv);
    printf("\n");
}