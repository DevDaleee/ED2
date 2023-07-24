#include <stdio.h>
#include <stdlib.h>
#include "imp23.h"
#include "impLista.h"

typedef struct Palavras{
    char Palavras[50];
    LPalavras *ListaLinhas;
}LPalavras;

typedef struct A23{
    LPalavras *palavra1, *palavra2;
    int NumInfos;
    Arv23 *esq, *dir, *center;
}Arv23;

void Arqv(Arv23** RaizArv23, LPalavras** PalavraSobe) {
    int Situacao; Situacao = 0;
    FILE *ArqPalavras;
    char BufferPalavra[50];
    int NumLinha; NumLinha = 1;

    ArqPalavras = fopen("../palavras.txt", "r");

    if (ArqPalavras == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }

    while (fscanf(ArqPalavras, "%s", BufferPalavra) != EOF) {
        InsereArv23(RaizArv23, NULL, PalavraSobe, BufferPalavra, NumLinha);
        NumLinha++;
    }
    NumLinha = 0;

    fclose(ArqPalavras);
}


Arv23* QuebraNo(Arv23** No, LPalavras** PalavraSobe, LPalavras* PalavraInfo, Arv23* Filho) {
    Arv23* MaiorNo; MaiorNo = NULL;

    int CompInfo1 = strcasecmp(PalavraInfo->Palavras, (*No)->palavra1->Palavras);
    int CompInfo2 = strcasecmp(PalavraInfo->Palavras, (*No)->palavra2->Palavras);

    if (CompInfo2 > 0) {
        (*PalavraSobe) = (*No)->palavra2;
        MaiorNo = EntradaDados(PalavraInfo, (*No)->dir, Filho, NULL);
    }
    else if (CompInfo1 > 0 && CompInfo2 < 0) {
        (*PalavraSobe) = PalavraInfo;
        MaiorNo = EntradaDados((*No)->palavra2, Filho, (*No)->dir, NULL);
    }
    else {
        (*PalavraSobe) = (*No)->palavra1;
        MaiorNo = EntradaDados((*No)->palavra2, (*No)->center, (*No)->dir, NULL);
        (*No)->center = Filho;
        (*No)->palavra1 = PalavraInfo;
    }

    (*No)->palavra2 = NULL;
    (*No)->dir = NULL;
    (*No)->NumInfos = 1;

    return (MaiorNo);
}

Arv23* EntradaDados(LPalavras* PalavraInfo, Arv23* Esq, Arv23* Centro, Arv23* Dir) {
    Arv23* NovoNo = (Arv23*) malloc(sizeof(Arv23));
    NovoNo->palavra1 = PalavraInfo;
    NovoNo->palavra2 = NULL;
    NovoNo->NumInfos = 1;
    NovoNo->esq = Esq;
    NovoNo->center = Centro;
    NovoNo->dir = Dir;

    return (NovoNo);
}