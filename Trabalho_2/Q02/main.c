#include <stdio.h>
#include <stdlib.h>
#include "imp23.h"

void Menu();
void ResetaArqTxt();
void GeraArqFinal();
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
            GeraArqFinal();
            puts("Um arquivo foi gerado com a situacao final do TXT manipulado no programa -> (arquivo_final.txt)");
            ResetaArqTxt();
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
            if (Situacao == 0){
                puts("Falha ao remover palavra");
            }
            else {
                puts("Palavra removida com sucesso!\n");    
            } 

            break;

        case 4:
            Op4(&RaizArv23, &Situacao);
            if (Situacao == 0){
                puts("Falha ao inserir palavra");
            }
            else {
                puts("Palavra inserida com sucesso!\n");    
            }
            break;
        case 5:
            Op5(&RaizArv23, &Situacao);
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
    printf("[3] - Excluir palavra de uma linha;\n");
    printf("[4] - Acrescentar palavra em uma linha;\n");
    printf("[5] - Remover palavra da arvore;\n");
    printf("[0] - Finalizar programa;\n");
    puts("---------------------------------");
    printf("Digite sua opcao: ");
}

void ResetaArqTxt() {
    FILE* ArqBackup, *ArqManipulavel;
    char linha[1000];
    ArqBackup = fopen("../dados_palavras_backup/palavras_1.txt", "r");
    ArqManipulavel = fopen("../dados_palavras/palavras_1.txt", "w");

    while (fgets(linha, 1000, ArqBackup) != NULL) {
        fprintf(ArqManipulavel, "%s", linha);
    }
    fclose(ArqBackup);
    fclose(ArqManipulavel);
}

void GeraArqFinal() {
    FILE* ArqProg, *ArqFinal;
    char linha[1000];
    ArqProg = fopen("../palavras_1.txt", "r");
    ArqFinal = fopen("../arquivo_final23.txt", "w");

    while (fgets(linha, 1000, ArqProg) != NULL) {
        fprintf(ArqFinal, "%s", linha);
    }
    fclose(ArqProg);
    fclose(ArqFinal);
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
    char Palavra[50];
    int linha;

    printf("Digite a palavra que deseja remover(Sem espaco): ");
    
    if(scanf("%s", Palavra) != 1){
        puts("ERRO ao digitar palavra");
    }
    else {
        printf("Digite a linha da palavra: ");
        scanf("%d", &linha);
        RemoverPalavraLinhaArq23(RaizArv23, Palavra, linha, Situacao);
    } 
    
}

void Op4(Arv23** RaizArv23, int* Situacao) {
    char Palavra[50];
    int linha;

    printf("Digite a palavra que deseja inserir(Sem espaco): ");
    if(scanf("%s", Palavra) != 1){
        puts("ERRO ao digitar palavra");
    }
    else {
        printf("Digite a linha onde a palavra sera inserida: ");
        scanf("%d", &linha);
        InserePalavraLinhaArq23(RaizArv23, Palavra, linha, Situacao);
    }
}

void Op5(Arv23** RaizArv23, int* Situacao) {
    char Palavra[100];

    printf("Digite a palavra a ser removida(Sem espaco): ");
    if(scanf("%s", Palavra) != 1){
        puts("ERRO ao digitar palavra");
    }
    else {
        RemovePalavra23(RaizArv23, NULL, Palavra, -1);
    }    
}