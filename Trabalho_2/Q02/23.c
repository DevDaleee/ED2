#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imp23.h"
#include "impLista.h"

struct _InfoPalavra {
    char Palavra[50];
    Linhas* ListaLinhas;
};

struct _Arv23 {
    InfoPalavra *Info1, *Info2;
    int NInfos;
    Arv23 *Esq, *Centro, *Dir;
};

void LeituraDadosArq(Arv23** RaizArv23, InfoPalavra** PalavraSobe) {
    int Situacao; Situacao = 0;
    FILE *ArqPalavras;
    char BufferPalavra[50];
    int NumLinha; NumLinha = 1;

    ArqPalavras = fopen("../teste.txt", "r");

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

Arv23* InsereArv23(Arv23** RaizArv23, Arv23* Pai, InfoPalavra** PalavraSobe, char* PalavraInfo, int LinhaPalavra) {
    Arv23* MaiorNo; MaiorNo = NULL;

    if ((*RaizArv23) == NULL) {
        InfoPalavra* NovaInfo = CriaInfoPalavra(PalavraInfo);
        InsereNoLinha(&(NovaInfo->ListaLinhas), LinhaPalavra);
        (*RaizArv23) = CriaNo23(NovaInfo, NULL, NULL, NULL);
    }
    else {
        if (VerificaFolha(*RaizArv23) == 1) {
            int CompInfo1 = strcasecmp(PalavraInfo, (*RaizArv23)->Info1->Palavra);
            if ((*RaizArv23)->NInfos == 1) {
                if (CompInfo1 == 0) {
                    InsereNoLinha(&((*RaizArv23)->Info1->ListaLinhas), LinhaPalavra);
                }
                else {
                    InfoPalavra* NovaInfo = CriaInfoPalavra(PalavraInfo);
                    InsereNoLinha(&(NovaInfo->ListaLinhas), LinhaPalavra);
                    AdicionaInfoNo(RaizArv23, NovaInfo, NULL);
                }
            }
            else {
                int CompInfo2 = strcasecmp(PalavraInfo, (*RaizArv23)->Info2->Palavra);

                if (CompInfo1 == 0) {
                    InsereNoLinha(&((*RaizArv23)->Info1->ListaLinhas), LinhaPalavra);    
                }
                else if (CompInfo2 == 0) {
                    InsereNoLinha(&((*RaizArv23)->Info2->ListaLinhas), LinhaPalavra);    
                }
                else {
                    InfoPalavra* NovaInfo = CriaInfoPalavra(PalavraInfo);
                    InsereNoLinha(&(NovaInfo->ListaLinhas), LinhaPalavra);
                    MaiorNo = QuebraNo(RaizArv23, PalavraSobe, NovaInfo, NULL);

                    if (Pai == NULL) {
                        (*RaizArv23) = CriaNo23((*PalavraSobe), (*RaizArv23), MaiorNo, NULL);
                        MaiorNo = NULL;
                    }
                }
            }
        }
        else {
            int CompInfo1 = strcasecmp(PalavraInfo, (*RaizArv23)->Info1->Palavra);
            int CompInfo2 = strcasecmp(PalavraInfo, (*RaizArv23)->Info2->Palavra);

            if (CompInfo1 == 0) {
                InsereNoLinha(&((*RaizArv23)->Info1->ListaLinhas), LinhaPalavra);
            }
            else if (CompInfo2 == 0) {
                InsereNoLinha(&((*RaizArv23)->Info2->ListaLinhas), LinhaPalavra);
            }
            else if (CompInfo1 < 0) {
                MaiorNo = InsereArv23(&((*RaizArv23)->Esq), *RaizArv23, PalavraSobe, PalavraInfo, LinhaPalavra);
            }
            else if (((*RaizArv23)->NInfos == 1 || ((*RaizArv23)->NInfos == 2)) && CompInfo2 < 0) {
                MaiorNo = InsereArv23(&((*RaizArv23)->Centro), *RaizArv23, PalavraSobe, PalavraInfo, LinhaPalavra);
            }
            else MaiorNo = InsereArv23(&((*RaizArv23)->Dir), *RaizArv23, PalavraSobe, PalavraInfo, LinhaPalavra);

            if (MaiorNo != NULL) {
                if((*RaizArv23)->NInfos == 1) {
                    AdicionaInfoNo(RaizArv23, (*PalavraSobe), MaiorNo);
                    MaiorNo = NULL;
                }
                else {
                    MaiorNo = QuebraNo(RaizArv23, PalavraSobe, *PalavraSobe, MaiorNo);

                    if (Pai == NULL) {
                        (*RaizArv23) = CriaNo23(*PalavraSobe, *RaizArv23, MaiorNo, NULL);
                        MaiorNo = NULL;
                    }
                }
            }
        }
    }

    return (MaiorNo);
}

Arv23* QuebraNo(Arv23** No, InfoPalavra** PalavraSobe, InfoPalavra* PalavraInfo, Arv23* Filho) {
    Arv23* MaiorNo; MaiorNo = NULL;

    int CompInfo1 = strcasecmp(PalavraInfo->Palavra, (*No)->Info1->Palavra);
    int CompInfo2 = strcasecmp(PalavraInfo->Palavra, (*No)->Info2->Palavra);

    if (CompInfo2 > 0) {
        (*PalavraSobe) = (*No)->Info2;
        MaiorNo = CriaNo23(PalavraInfo, (*No)->Dir, Filho, NULL);
    }
    else if (CompInfo1 > 0 && CompInfo2 < 0) {
        (*PalavraSobe) = PalavraInfo;
        MaiorNo = CriaNo23((*No)->Info2, Filho, (*No)->Dir, NULL);
    }
    else {
        (*PalavraSobe) = (*No)->Info1;
        MaiorNo = CriaNo23((*No)->Info2, (*No)->Centro, (*No)->Dir, NULL);
        (*No)->Centro = Filho;
        (*No)->Info1 = PalavraInfo;
    }

    (*No)->Info2 = NULL;
    (*No)->Dir = NULL;
    (*No)->NInfos = 1;

    return (MaiorNo);
}

void AdicionaInfoNo(Arv23 **RaizArv23, InfoPalavra* PalavraInfo, Arv23* Filho) {
    int CompPalavras = strcasecmp(PalavraInfo->Palavra, (*RaizArv23)->Info1->Palavra);

    if (CompPalavras < 0) {
        (*RaizArv23)->Info2 = (*RaizArv23)->Info1;
        (*RaizArv23)->Info1 = PalavraInfo;
        (*RaizArv23)->Dir = (*RaizArv23)->Centro;
        (*RaizArv23)->Centro = Filho; 
    }
    else if (CompPalavras > 0) {
        (*RaizArv23)->Info2 = PalavraInfo;
        (*RaizArv23)->Dir = Filho;
    }

    (*RaizArv23)->NInfos = 2;
}

Arv23* CriaNo23(InfoPalavra* PalavraInfo, Arv23* Esq, Arv23* Centro, Arv23* Dir) {
    Arv23* NovoNo = (Arv23*) malloc(sizeof(Arv23));
    NovoNo->Info1 = PalavraInfo;
    NovoNo->Info2 = NULL;
    NovoNo->NInfos = 1;
    NovoNo->Esq = Esq;
    NovoNo->Centro = Centro;
    NovoNo->Dir = Dir;

    return (NovoNo);
}

InfoPalavra* CriaInfoPalavra(char* Palavra) {
    InfoPalavra* NovaInfoPalavra = (InfoPalavra*) malloc(sizeof(InfoPalavra));
    strcpy(NovaInfoPalavra->Palavra, Palavra);
    NovaInfoPalavra->ListaLinhas = NULL;
}

int VerificaFolha(Arv23* NoArv23) {
    int EhFolha = 0;
    if (NoArv23->Esq == NULL && NoArv23->Centro == NULL) {
        EhFolha = 1;
    }

    return (EhFolha);
}

/*InfoPalavra* BuscaArv23Teste(Arv23* RaizArv23, char* PalavraBusca, int* NosPercorridos) {
    InfoPalavra* InfoBusca;
    if (RaizArv23 != NULL) {
        (*NosPercorridos)++;
        int Comp1, Comp2;
        Comp1 = strcasecmp(PalavraBusca, RaizArv23->Info1->Palavra);
        Comp2 = strcasecmp(PalavraBusca, RaizArv23->Info2->Palavra);
        if (Comp1 == 0) {
            InfoBusca = RaizArv23->Info1;
        }
        else if (Comp2 == 0) {
            InfoBusca = RaizArv23->Info2;
        }
        else if (Comp1 < 0) {
            InfoBusca = BuscaArv23Teste(RaizArv23->Esq, PalavraBusca, NosPercorridos);
        }
        else if (RaizArv23->NInfos >= 1 && Comp2 < 0) {
            InfoBusca = BuscaArv23Teste(RaizArv23->Centro, PalavraBusca, NosPercorridos);
        }
        else {
            InfoBusca = BuscaArv23Teste(RaizArv23->Dir, PalavraBusca, NosPercorridos);
        }   
    }
    else {
        InfoBusca = NULL;
    }

    return (InfoBusca);
}*/

InfoPalavra* BuscaInfo23(Arv23* RaizArv23, char* Palavra) {
    InfoPalavra* InfoBusca;
    if (RaizArv23 != NULL) {
        int ValorPalavra1 = strcasecmp(Palavra, RaizArv23->Info1->Palavra);
        int ValorPalavra2 = strcasecmp(Palavra, RaizArv23->Info2->Palavra);    

        if (ValorPalavra1 == 0) {
            InfoBusca = RaizArv23->Info1;
        }
        else if(ValorPalavra2 == 0) {
            InfoBusca = RaizArv23->Info2;
        }
        else if (ValorPalavra1 < 1) {
            InfoBusca = BuscaInfo23(RaizArv23->Esq, Palavra);
        }
        else if (RaizArv23->NInfos == 1 || RaizArv23->NInfos == 2 && ValorPalavra2 < 0) {
            InfoBusca = BuscaInfo23(RaizArv23->Centro, Palavra);   
        }
        else {
            InfoBusca = BuscaInfo23(RaizArv23->Dir, Palavra);
        }
    }
    else {
        InfoBusca = NULL;
    }

    return(InfoBusca);
}

void ImprimeInfo(InfoPalavra* InfoNo) {
    printf("%s | Linhas-> ", InfoNo->Palavra);
    ImprimeListaLinhas(InfoNo->ListaLinhas);
}

void ImprimeNo23(Arv23* No) {
    printf("%s | Linhas-> ", No->Info1->Palavra);
    ImprimeListaLinhas(No->Info1->ListaLinhas);
    printf("\n");

    if (No->NInfos == 2) {
        printf("%s | Linhas-> ", No->Info2->Palavra);
        ImprimeListaLinhas(No->Info2->ListaLinhas);
        printf("\n");
    }
    //printf("NInfos %d\n", No->NInfos);    
}

void ImprimeArv23(Arv23 *RaizArv23, int nivel) {
    if (RaizArv23 != NULL) {
        // Imprimir os valores do nível atual
        ImprimeArv23(RaizArv23->Esq, 0);
        ImprimeNo23(RaizArv23);
        ImprimeArv23(RaizArv23->Centro, 0);
        ImprimeArv23(RaizArv23->Dir, 0);

        /*for (int i = 0; i < nivel; i++) {
            printf("\t");
        }

        printf("Nivel %d: ", nivel);
        
        // Imprimir os valores de acordo com o número de informações presentes no nó
        printf("%s ", RaizArv23->Info1->Palavra);
        printf("Linhas -- ");
        ImprimeListaLinhas(RaizArv23->Info1->ListaLinhas);
        
        if (RaizArv23->NInfos == 2) {
            printf("%s ", RaizArv23->Info2->Palavra);
            printf("Linhas -- ");
            ImprimeListaLinhas(RaizArv23->Info2->ListaLinhas);
        }
        printf("NInfos %d\n", RaizArv23->NInfos);

        // Recursivamente imprimir os filhos
        ImprimeArv23(RaizArv23->Esq, nivel + 1);
        ImprimeArv23(RaizArv23->Centro, nivel + 1);
        ImprimeArv23(RaizArv23->Dir, nivel + 1);*/
    }
}

void removeQuebrasDeLinha(char *str) {
    int len = strlen(str);
    if (len > 0) {
        if (str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }
        if (len > 0 && str[len - 1] == '\r') {
            str[len - 1] = '\0';
        }
    }
}

void RemoverPalavraLinhaArq23(Arv23** RaizArv23, char* Palavra, int LinhaPalavra, int* Situacao) {
    char inputFileName[] = "../palavras_1.txt";
    char outputFileName[] = "../temp.txt";

    FILE *inputFile, *outputFile;
    char linha[100];
    int encontrouPalavra;
    int LinhaN = 1;

    inputFile = fopen(inputFileName, "r");
    outputFile = fopen(outputFileName, "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        *Situacao = 0;
    }

    int ValorComp;
    while (fgets(linha, 100, inputFile) != NULL) {
        if (LinhaN == LinhaPalavra){
            char *palavraLinha = strtok(linha, ",\n"); // Considera também a quebra de linha
            encontrouPalavra = 0;

            while (palavraLinha != NULL) {
                removeQuebrasDeLinha(palavraLinha);
                if (strcasecmp(palavraLinha, Palavra) != 0) {
                    fprintf(outputFile, "%s", palavraLinha);
                }
                else {
                    *Situacao = 1;
                    fprintf(outputFile, "%s", "X");
                    RemovePalavra23(RaizArv23, NULL, Palavra, LinhaPalavra);
                }

                palavraLinha = strtok(NULL, ",\n");
                if (palavraLinha)
                    fprintf(outputFile, ",");
            }
            fprintf(outputFile, "\n"); // Quebra de linha ao final de cada linha
        }
        else {
            fprintf(outputFile, "%s", linha);
        }

        LinhaN++;
    }

    fclose(inputFile);
    fclose(outputFile);

    if (remove(inputFileName) != 0) {
        *Situacao = 0;
    }
    if (rename(outputFileName, inputFileName) != 0) {
        *Situacao = 0;
    }
}

void InserePalavraLinhaArq23(Arv23** RaizArv23, char* Palavra, int LinhaPalavra, int* Situacao) {
    char inputFileName[] = "../palavras_1.txt";
    char outputFileName[] = "../temp.txt";
    FILE *inputFile, *outputFile;
    int LinhaN; LinhaN = 0;
    char linha[100];

    inputFile = fopen(inputFileName, "r");
    outputFile = fopen(outputFileName, "w");
    if (inputFile == NULL || outputFile == NULL) {
        *Situacao = 0;
    }

    InfoPalavra *PalavraSobe; PalavraSobe = NULL;
    while (fgets(linha, 100, inputFile) != NULL) {
        LinhaN++;
        if (LinhaN == LinhaPalavra) {
            // Verifica se a linha está vazia ou não
            if (strlen(linha) == 1 && linha[0] == '\n') { // A linha contém apenas o caractere '\n'
                fprintf(outputFile, "%s\n", Palavra);
            } else {
                linha[strcspn(linha, "\n\r")] = '\0';
                // Acrescentar a vírgula e a palavra
                fprintf(outputFile, "%s,%s\n", linha, Palavra);
                InsereArv23(RaizArv23, NULL, &PalavraSobe, Palavra, LinhaPalavra);
            }
            *Situacao = 1;
        } else {
            fprintf(outputFile, "%s", linha);
        }

    }

    fclose(inputFile);
    fclose(outputFile);

    if (remove(inputFileName) != 0) {
        *Situacao = 0;
    }
    if (rename(outputFileName, inputFileName) != 0) {
        *Situacao = 0;
    }
}

void RemoveMaiorInfoEsq(Arv23** RaizArv23, Arv23** PaiMaior, Arv23** MaiorInfoRemove, int LocalInfo) {
    if (MaiorInfoRemove != NULL) {
        if (VerificaFolha(*MaiorInfoRemove) == 1) {
            InfoPalavra* Aux;
            if (LocalInfo == 1) {
                Aux = (*RaizArv23)->Info1;

                if ((*MaiorInfoRemove)->NInfos == 2) {
                    (*RaizArv23)->Info1 = (*MaiorInfoRemove)->Info2;
                    (*MaiorInfoRemove)->Info2 = Aux;
                }
                else {
                    (*RaizArv23)->Info1 = (*MaiorInfoRemove)->Info1;
                    (*MaiorInfoRemove)->Info1 = Aux;
                }

            }
            else if (LocalInfo == 2) {
                Aux = (*RaizArv23)->Info2;

                if ((*MaiorInfoRemove)->NInfos == 2) {
                    (*RaizArv23)->Info2 = (*MaiorInfoRemove)->Info2;
                    (*MaiorInfoRemove)->Info2 = Aux;
                }
                else {
                    (*RaizArv23)->Info2 = (*MaiorInfoRemove)->Info1;
                    (*MaiorInfoRemove)->Info1 = Aux;
                }

            }

            RemovePalavra23(MaiorInfoRemove, PaiMaior, Aux->Palavra, -1);
        }
        else {
            if ((*MaiorInfoRemove)->NInfos == 2) {
                RemoveMaiorInfoEsq(RaizArv23, MaiorInfoRemove, &((*MaiorInfoRemove)->Dir), LocalInfo);
            }
            else if ((*MaiorInfoRemove)->NInfos == 1) {
                RemoveMaiorInfoEsq(RaizArv23, MaiorInfoRemove, &((*MaiorInfoRemove)->Centro), LocalInfo);
            }
        } 
    }
    RedistribuiArv23(MaiorInfoRemove, PaiMaior);
}

void RemovePalavra23(Arv23** RaizArv23, Arv23** Pai, char* Palavra, int LinhaPalavra) {
    if (*RaizArv23 != NULL) {
        if (strcasecmp(Palavra, (*RaizArv23)->Info1->Palavra) == 0) {
            if (LinhaPalavra == -1) {
                if (VerificaFolha(*RaizArv23) == 1) {
                    if ((*RaizArv23)->NInfos == 2) {
                        free((*RaizArv23)->Info1);
                        (*RaizArv23)->Info1 = (*RaizArv23)->Info2;
                        (*RaizArv23)->Info2 = NULL;
                        (*RaizArv23)->NInfos = 1;
                    }
                    else if ((*RaizArv23)->NInfos == 1){
                        free((*RaizArv23)->Info1);
                        (*RaizArv23)->Info1 = NULL;
                        (*RaizArv23)->NInfos = 0;
                    }
                }
                else {
                    Arv23 **MaiorInfoRemove = &((*RaizArv23)->Esq);
                    Arv23 **PaiMaior = RaizArv23;
                    RemoveMaiorInfoEsq(RaizArv23, PaiMaior, MaiorInfoRemove, 1);
                }
            }
            else {
                RemoveNoLinha(&((*RaizArv23)->Info1->ListaLinhas), LinhaPalavra);
                if ((*RaizArv23)->Info1->ListaLinhas == NULL) {
                    RemovePalavra23(RaizArv23, Pai, Palavra, -1);
                }
            }
        }
        else if ((*RaizArv23)->NInfos == 2 && strcasecmp(Palavra, (*RaizArv23)->Info2->Palavra) == 0) {
            
            if (LinhaPalavra == -1) {
                if (VerificaFolha(*RaizArv23) == 1) {
                    free((*RaizArv23)->Info2);
                    (*RaizArv23)->Info2 = NULL;
                    (*RaizArv23)->NInfos = 1;
                }
                else {
                    Arv23 **MaiorInfoRemove = &((*RaizArv23)->Centro);
                    Arv23 **PaiMaior = RaizArv23;
                    RemoveMaiorInfoEsq(RaizArv23, PaiMaior, MaiorInfoRemove, 2);
                }
            }
            else {
                RemoveNoLinha(&((*RaizArv23)->Info2->ListaLinhas), LinhaPalavra);
                if ((*RaizArv23)->Info2->ListaLinhas == NULL) {
                    RemovePalavra23(RaizArv23, Pai, Palavra, -1);
                }    
            }
        }
		else if (strcasecmp(Palavra, (*RaizArv23)->Info1->Palavra) < 0) {
            RemovePalavra23(&((*RaizArv23)->Esq), RaizArv23, Palavra, LinhaPalavra);
        }
        else if ((*RaizArv23)->NInfos == 1 || (*RaizArv23)->NInfos == 2 && strcasecmp(Palavra, (*RaizArv23)->Info2->Palavra) < 0) {
            RemovePalavra23(&((*RaizArv23)->Centro), RaizArv23, Palavra, LinhaPalavra);
        }
        else {
            RemovePalavra23(&((*RaizArv23)->Dir), RaizArv23, Palavra, LinhaPalavra);
        }
    }
    RedistribuiArv23(RaizArv23, Pai);
}

void RedistribuiArv23(Arv23** RaizArv23, Arv23** Pai) {
    if (*RaizArv23 != NULL)
        if ((*RaizArv23)->NInfos == 0) {
            if (Pai != NULL) {
                if ((*RaizArv23) == ((*Pai)->Dir)) {
                    if ((*Pai)->Centro->NInfos == 2) {
                        (*RaizArv23)->Info1 = (*Pai)->Info2;
                        (*RaizArv23)->NInfos = 1;
                        (*Pai)->Info2 = (*Pai)->Centro->Info2;
                        (*Pai)->Centro->NInfos = 1;
                        (*Pai)->Centro->Info2 = NULL;
                        (*RaizArv23)->Esq = (*Pai)->Centro->Dir;
                        (*Pai)->Centro->Dir = NULL;
                    }
                    else if ((*Pai)->Centro->NInfos == 1) {
                        (*RaizArv23)->Info2 = (*Pai)->Info2;
                        (*RaizArv23)->Dir = (*RaizArv23)->Centro;
                        (*RaizArv23)->Info1 = (*Pai)->Centro->Info1;
                        (*RaizArv23)->NInfos = 2;
                        (*Pai)->NInfos = 1;
                        (*RaizArv23)->Centro = (*Pai)->Centro->Centro;
                        (*RaizArv23)->Esq = (*Pai)->Centro->Esq;
                        free((*Pai)->Centro);
                        (*Pai)->Centro = (*RaizArv23);
                        (*Pai)->Dir = NULL;
                    }
                }
                else if ((*RaizArv23) == (*Pai)->Centro) {
                    if ((*Pai)->Esq->NInfos == 2) {
                        (*RaizArv23)->Info1 = (*Pai)->Info1;
                        (*RaizArv23)->NInfos = 1;
                        (*Pai)->Info1 = (*Pai)->Esq->Info2;
                        (*Pai)->Esq->NInfos = 1;
                        (*RaizArv23)->Esq = (*Pai)->Esq->Dir;
                        (*Pai)->Esq->Dir = NULL;
                    }
                    else if ((*Pai)->Esq->NInfos == 1) {
                        if ((*Pai)->NInfos == 2) {
                            (*RaizArv23)->Info2 = (*Pai)->Info1;
                            (*RaizArv23)->Info1 = (*Pai)->Esq->Info1;
                            (*RaizArv23)->NInfos = 2;
                            (*RaizArv23)->Dir = (*RaizArv23)->Centro;
                            (*RaizArv23)->Centro = (*Pai)->Esq->Centro;
                            (*RaizArv23)->Esq = (*Pai)->Esq->Esq;
                            free((*Pai)->Esq);
                            (*Pai)->Esq = (*RaizArv23);
                            (*Pai)->Info1 = (*Pai)->Info2;
                            (*Pai)->NInfos = 1;
                            (*Pai)->Centro = (*Pai)->Dir;
                            (*Pai)->Dir = NULL;
                        }
                        else if ((*Pai)->NInfos == 1) {
                            (*RaizArv23)->Info2 = (*Pai)->Info1;
                            (*RaizArv23)->Info1 = (*Pai)->Esq->Info1;
                            (*RaizArv23)->NInfos = 2;
                            (*Pai)->NInfos = 0;
                            (*RaizArv23)->Dir = (*RaizArv23)->Centro;
                            (*RaizArv23)->Centro = (*Pai)->Esq->Centro;
                            (*RaizArv23)->Esq = (*Pai)->Esq->Esq;
                            free((*Pai)->Esq);
                            (*Pai)->Esq = NULL;
                        }
                    }
                }
                else if ((*RaizArv23) == (*Pai)->Esq) {
                    if ((*Pai)->Centro->NInfos == 2) {
                        (*RaizArv23)->Info1 = (*Pai)->Info1;
                        (*RaizArv23)->NInfos = 1;
                        (*Pai)->Info1 = (*Pai)->Centro->Info1;
                        (*Pai)->Centro->NInfos = 1;
                        (*Pai)->Centro->Info1 = (*Pai)->Centro->Info2;
                        (*RaizArv23)->Esq = (*RaizArv23)->Centro;
                        (*RaizArv23)->Centro = (*Pai)->Centro->Esq;
                        (*Pai)->Centro->Esq = (*Pai)->Centro->Centro;
                        (*Pai)->Centro->Centro = (*Pai)->Centro->Dir;
                        (*Pai)->Centro->Dir = NULL;
                    }
                    else if ((*Pai)->Centro->NInfos == 1) {
                        if ((*Pai)->NInfos == 2) {
                            (*RaizArv23)->Info1 = (*Pai)->Info1;
                            (*RaizArv23)->Info2 = (*Pai)->Centro->Info1;
                            (*RaizArv23)->NInfos = 2;
                            (*RaizArv23)->Esq = (*RaizArv23)->Centro;
                            (*RaizArv23)->Centro = (*Pai)->Centro->Esq;
                            (*RaizArv23)->Dir = (*Pai)->Centro->Centro;
                            (*Pai)->Info1 = (*Pai)->Info2;
                            (*Pai)->NInfos = 1;
                            free((*Pai)->Centro);
                            (*Pai)->Centro = (*Pai)->Dir;
                            (*Pai)->Dir = NULL;
                        }
                        else if ((*Pai)->NInfos == 1) {
                            (*RaizArv23)->Info1 = (*Pai)->Info1;
                            (*RaizArv23)->Esq = (*RaizArv23)->Centro;
                            (*RaizArv23)->Info2 = (*Pai)->Centro->Info1;
                            (*RaizArv23)->Centro = (*Pai)->Centro->Esq;
                            (*RaizArv23)->Dir = (*Pai)->Centro->Centro;
                            (*Pai)->NInfos = 0;
                            (*RaizArv23)->NInfos = 2;
                            free((*Pai)->Centro);
                            (*Pai)->Centro = (*RaizArv23);
                            (*Pai)->Esq = NULL;
                        }
                    }
                }
            }
            else if (Pai == NULL) {
                (*RaizArv23) = (*RaizArv23)->Centro;
            }  
        }
}