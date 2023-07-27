#include <stdio.h>
#include <stdlib.h>
#include "23.h"

void Menu();
void Op2(Arv23* RaizArv23, int* Situacao);
void Op3(Arv23** RaizArv23, int* Situacao);
void Op4(Arv23** RaizArv23, int* Situacao);
void Op5(Arv23** RaizArv23, int* Situacao);

int main () {
    Arv23* RaizArv23; RaizArv23 = NULL;
    InfoPalavra* PalavraSobe; PalavraSobe = NULL;
    int Situacao, Opcao; Opcao = 0;

    LeituraDadosArq(&RaizArv23, &PalavraSobe);
    do
    {
        Menu();
        scanf("%d", &Opcao);
        puts("---------------------------------");

        switch (Opcao)
        {
        case 0:
            puts("Finalizando...");
            break;

        case 1:
            if (RaizArv23 == NULL) {
                puts("Árvore vazia!");
            }
            else {
                ImprimeArv23(RaizArv23, 0);
            }

            break;

        case 2:
            Op2(RaizArv23, &Situacao);
            if (Situacao == 0) {
                puts("Palavra nao encontrada");
            }
            else {
                puts("Operacao realizada com sucesso!");
            }
            break;
        
        case 3:
            Op3(&RaizArv23, &Situacao);
            break;
        default:
            puts("Opcao invalida!");

            break;
        }

        Situacao = 0;
    } while (Opcao != 0);

    return 0;
}

void Menu() {
    puts("---------------------------------");
    printf("[1] - Imprimir palavras;\n");
    printf("[2] - Busca palavra;\n");
    printf("[3] - Remover palavra da arvore;\n");
    printf("[0] - Finalizar programa;\n");
    puts("---------------------------------");
    printf("Digite sua opcao: ");
}


void Op2(Arv23* RaizArv23, int* Situacao) {
    char Palavra[50];
    InfoPalavra* InfoBusca;

    printf("Digite a palavra a ser buscada(Sem espaco): ");
    if(scanf("%s", Palavra) != 1)
        puts("ERRO ao digitar palavra");
    else 
        InfoBusca = BuscaInfo23(RaizArv23, Palavra);
        if (InfoBusca == NULL){
            *Situacao = 0;
        }
        else{
            *Situacao = 1;
            ImprimeInfo(InfoBusca);
        }
}

void Op3(Arv23** RaizArv23, int* Situacao) {
    char Palavra[100];

    printf("Digite a palavra a ser removida(Sem espaco): ");
    if(scanf("%s", Palavra) != 1){
        puts("ERRO ao digitar palavra");
    }
    else {
        RemovePalavra23(RaizArv23, NULL, Palavra, -1);
    }    
}