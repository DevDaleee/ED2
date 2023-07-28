#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "impLLRB.h"

void menu() {
    printf("\n\t\tMENU\n");
    puts("-----------------------------");
    printf("[1] - Imprimir palavras.\n");
    printf("[2] - Busca palavra.\n");
    printf("[3] - Adicionar uma palavra.\n");
    printf("[0] - Finalizar programa.\n");
    puts("-----------------------------");
}

int main (){
    ArvRN *RaizArv;
    RaizArv = NULL;
    int op = 0;

    FILE *file;
    file = fopen("../teste.txt", "r");

    if (file == NULL) {
        printf("Erro ao Abrir o Arquivo! \n");
        return 0;
    }

    char palavra[100];  
    int repetidas = 1;

    while(fscanf(file, "%s", palavra) != EOF){
        inserir(&RaizArv, palavra, repetidas);
        repetidas++;
    }
    repetidas = 0;
    fclose(file);

    do
    {
        menu();
        printf("Digite uma opcao: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            if (RaizArv == NULL) {
                puts("Árvore vazia!");
            }
            else {
                ImprimeArvoreInOrdemLLRB(RaizArv);
            }
            break;

        case 2:
            char palavra2[50];
            printf("Digite a palavra que deseja buscar: ");
            scanf("%s", palavra2);
            BuscarPalavra(RaizArv, palavra2);
            
            break;
        
        case 3:
            char Palavra2[50];

            printf("Digite uma palavra: ");
            scanf("%s", Palavra2);
            inserir(&RaizArv, Palavra2, repetidas=1);

            break;

        case 0:
            printf("Finalizado!\n");
            break;

        default:
            puts("Opcao invalida!");
            break;
        }
    } while (op != 0);


}