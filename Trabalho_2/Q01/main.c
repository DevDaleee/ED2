#include <stdio.h>
#include <stdlib.h>
#include "impLLRB.h"


int main(){
    ArvRN *RaizArv;
    RaizArv = NULL;

    inserir(&(RaizArv), 10);
    inserir(&(RaizArv), 20);
    inserir(&(RaizArv), 30);
    inserir(&(RaizArv), 40);

    ImprimeArvoreInOrdemLLRB(RaizArv);
    printf("\n");
    
}