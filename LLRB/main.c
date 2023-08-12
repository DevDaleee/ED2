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

    ImprimeArvoreInOrdemLLRB(RaizArv);
    printf("\n");
    
    removerLLRB(&(RaizArv), 20);
    ImprimeArvoreInOrdemLLRB(RaizArv);
    printf("\n");
    
}