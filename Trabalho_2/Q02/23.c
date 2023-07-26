#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "23.h"
#include "impLista.h"

struct _InfoPalavra {
    char Palavra[50];
    Linhas* ListaLinhas;
};

struct _Arv23 {
    InfoPalavra *Info1, *Info2;
    int NInfos;
    Arv23 *esq, *center, *dir;
};

void LeituraDadosArq(Arv23** RaizArv23, InfoPalavra** PalavraSobe) {
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

Arv23* InsereArv23(Arv23** RaizArv23, Arv23* Pai, InfoPalavra** PalavraSobe, char* PalavraInfo, int LinhaPalavra) {
    Arv23* MaiorNo; MaiorNo = NULL;

    if ((*RaizArv23) == NULL) {
        InfoPalavra* NovaInfo = CriaInfoPalavra(PalavraInfo);
        InsereNoLinha(&(NovaInfo->ListaLinhas), LinhaPalavra);
        (*RaizArv23) = CriaNo23(NovaInfo, NULL, NULL, NULL);
    } else {
        if (VerificaFolha(*RaizArv23) == 1) {
            int CompInfo1 = strcasecmp(PalavraInfo, (*RaizArv23)->Info1->Palavra);
            if ((*RaizArv23)->NInfos == 1) {
                if (CompInfo1 == 0) {
                    InsereNoLinha(&((*RaizArv23)->Info1->ListaLinhas), LinhaPalavra);
                } else {
                    InfoPalavra* NovaInfo = CriaInfoPalavra(PalavraInfo);
                    InsereNoLinha(&(NovaInfo->ListaLinhas), LinhaPalavra);
                    AdicionaInfoNo(RaizArv23, NovaInfo, NULL);
                }
            }
            else {
                int CompInfo2 = strcasecmp(PalavraInfo, (*RaizArv23)->Info2->Palavra);

                if (CompInfo1 == 0) {
                    InsereNoLinha(&((*RaizArv23)->Info1->ListaLinhas), LinhaPalavra);    
                } else if (CompInfo2 == 0) {
                    InsereNoLinha(&((*RaizArv23)->Info2->ListaLinhas), LinhaPalavra);    
                } else {
                    InfoPalavra* NovaInfo = CriaInfoPalavra(PalavraInfo);
                    InsereNoLinha(&(NovaInfo->ListaLinhas), LinhaPalavra);
                    MaiorNo = QuebraNo(RaizArv23, PalavraSobe, NovaInfo, NULL);

                    if (Pai == NULL) {
                        (*RaizArv23) = CriaNo23((*PalavraSobe), (*RaizArv23), MaiorNo, NULL);
                        MaiorNo = NULL;
                    }
                }
            }
        } else {
            int CompInfo1 = strcasecmp(PalavraInfo, (*RaizArv23)->Info1->Palavra);
            int CompInfo2; CompInfo2 = -1;
            if ((*RaizArv23)->NInfos == 2) {
                CompInfo2 = strcasecmp(PalavraInfo, (*RaizArv23)->Info2->Palavra);
            }

            if (CompInfo1 == 0) {
                InsereNoLinha(&((*RaizArv23)->Info1->ListaLinhas), LinhaPalavra);
            } else if (CompInfo2 == 0) {
                InsereNoLinha(&((*RaizArv23)->Info2->ListaLinhas), LinhaPalavra);
            } else if (CompInfo1 < 0) {
                MaiorNo = InsereArv23(&((*RaizArv23)->esq), *RaizArv23, PalavraSobe, PalavraInfo, LinhaPalavra);
            } else if (((*RaizArv23)->NInfos == 1 || (*RaizArv23)->NInfos == 2) && CompInfo2 < 0) {
                MaiorNo = InsereArv23(&((*RaizArv23)->center), *RaizArv23, PalavraSobe, PalavraInfo, LinhaPalavra);
            } else  MaiorNo = InsereArv23(&((*RaizArv23)->dir), *RaizArv23, PalavraSobe, PalavraInfo, LinhaPalavra);

            if (MaiorNo != NULL) {
                if((*RaizArv23)->NInfos == 1) {
                    AdicionaInfoNo(RaizArv23, *PalavraSobe, MaiorNo);
                    MaiorNo = NULL;
                } else {
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
        MaiorNo = CriaNo23(PalavraInfo, (*No)->dir, Filho, NULL);
    } else if (CompInfo1 > 0 && CompInfo2 < 0) {
        (*PalavraSobe) = PalavraInfo;
        MaiorNo = CriaNo23((*No)->Info2, Filho, (*No)->dir, NULL);
    } else {
        (*PalavraSobe) = (*No)->Info1;
        MaiorNo = CriaNo23((*No)->Info2, (*No)->center, (*No)->dir, NULL);
        (*No)->center = Filho;
        (*No)->Info1 = PalavraInfo;
    }
    (*No)->Info2 = NULL;
    (*No)->dir = NULL;
    (*No)->NInfos = 1;

    return (MaiorNo);
}

void AdicionaInfoNo(Arv23 **RaizArv23, InfoPalavra* PalavraInfo, Arv23* Filho) {
    int CompPalavras = strcasecmp(PalavraInfo->Palavra, (*RaizArv23)->Info1->Palavra);

    if (CompPalavras < 0) {
        (*RaizArv23)->Info2 = (*RaizArv23)->Info1;
        (*RaizArv23)->Info1 = PalavraInfo;
        (*RaizArv23)->dir = (*RaizArv23)->center;
        (*RaizArv23)->center = Filho; 
    } else if (CompPalavras > 0) {
        (*RaizArv23)->Info2 = PalavraInfo;
        (*RaizArv23)->dir = Filho;
    }

    (*RaizArv23)->NInfos = 2;
}

Arv23* CriaNo23(InfoPalavra* PalavraInfo, Arv23* Esq, Arv23* Centro, Arv23* Dir) {
    Arv23* NovoNo = (Arv23*) malloc(sizeof(Arv23));
    NovoNo->Info1 = PalavraInfo;
    NovoNo->Info2 = NULL;
    NovoNo->NInfos = 1;
    NovoNo->esq = Esq;
    NovoNo->center = Centro;
    NovoNo->dir = Dir;

    return (NovoNo);
}

InfoPalavra* CriaInfoPalavra(char* Palavra) {
    InfoPalavra* NovaInfoPalavra = (InfoPalavra*) malloc(sizeof(InfoPalavra));
    strcpy(NovaInfoPalavra->Palavra, Palavra);
    NovaInfoPalavra->ListaLinhas = NULL;
    return NovaInfoPalavra;
}

int VerificaFolha(Arv23* NoArv23) {
    int EhFolha = 0;
    if (NoArv23->esq == NULL && NoArv23->center == NULL) {
        EhFolha = 1;
    }
    return (EhFolha);
}

InfoPalavra* BuscaInfo23(Arv23* RaizArv23, char* Palavra) {
    InfoPalavra* InfoBuscada = NULL;
    if (RaizArv23 != NULL) {
        if (strcasecmp(Palavra, RaizArv23->Info1->Palavra) == 0) {
            InfoBuscada = RaizArv23->Info1;
        } else if (RaizArv23->NInfos == 2 && strcasecmp(Palavra, RaizArv23->Info2->Palavra) == 0) {
            InfoBuscada = RaizArv23->Info2;
        } else if (strcasecmp(Palavra, RaizArv23->Info1->Palavra) < 0) {
            InfoBuscada = BuscaInfo23(RaizArv23->esq, Palavra);
        } else if (RaizArv23->NInfos == 1 || RaizArv23->NInfos == 2 && strcasecmp(Palavra, RaizArv23->Info2->Palavra) < 0) {
            InfoBuscada = BuscaInfo23(RaizArv23->center, Palavra);
        } else {
            InfoBuscada = BuscaInfo23(RaizArv23->dir, Palavra);
        }
    }
    return (InfoBuscada);
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
        ImprimeArv23(RaizArv23->esq, 0);
        ImprimeInfo(RaizArv23->Info1);
        printf("\n");

        ImprimeArv23(RaizArv23->center, 0);
        if (RaizArv23->NInfos == 2) {
            ImprimeInfo(RaizArv23->Info2);
            printf("\n");
        }
        ImprimeArv23(RaizArv23->dir, 0);
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

void RemoveMaiorInfoEsq(Arv23** RaizArv23, Arv23** PaiMaior, Arv23** MaiorInfoRemove, int LocalInfo) {
    if (MaiorInfoRemove != NULL) {
        if (VerificaFolha(*MaiorInfoRemove) == 1) {
            InfoPalavra* Aux;
            if (LocalInfo == 1) {
                Aux = (*RaizArv23)->Info1;

                if ((*MaiorInfoRemove)->NInfos == 2) {
                    (*RaizArv23)->Info1 = (*MaiorInfoRemove)->Info2;
                    (*MaiorInfoRemove)->Info2 = Aux;
                } else {
                    (*RaizArv23)->Info1 = (*MaiorInfoRemove)->Info1;
                    (*MaiorInfoRemove)->Info1 = Aux;
                }

            } else if (LocalInfo == 2) {
                Aux = (*RaizArv23)->Info2;

                if ((*MaiorInfoRemove)->NInfos == 2) {
                    (*RaizArv23)->Info2 = (*MaiorInfoRemove)->Info2;
                    (*MaiorInfoRemove)->Info2 = Aux;
                } else {
                    (*RaizArv23)->Info2 = (*MaiorInfoRemove)->Info1;
                    (*MaiorInfoRemove)->Info1 = Aux;
                }

            }

            RemovePalavra23(MaiorInfoRemove, PaiMaior, Aux->Palavra, -1);
        } else {
            if ((*MaiorInfoRemove)->NInfos == 2) {
                RemoveMaiorInfoEsq(RaizArv23, MaiorInfoRemove, &((*MaiorInfoRemove)->dir), LocalInfo);
            } else if ((*MaiorInfoRemove)->NInfos == 1) {
                RemoveMaiorInfoEsq(RaizArv23, MaiorInfoRemove, &((*MaiorInfoRemove)->center), LocalInfo);
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
                    } else if ((*RaizArv23)->NInfos == 1){
                        free((*RaizArv23)->Info1);
                        (*RaizArv23)->Info1 = NULL;
                        (*RaizArv23)->NInfos = 0;
                    }
                } else {
                    Arv23 **MaiorInfoRemove = &((*RaizArv23)->esq);
                    Arv23 **PaiMaior = RaizArv23;
                    RemoveMaiorInfoEsq(RaizArv23, PaiMaior, MaiorInfoRemove, 1);
                }
            } else {
                RemoveNoLinha(&((*RaizArv23)->Info1->ListaLinhas), LinhaPalavra);
                if ((*RaizArv23)->Info1->ListaLinhas == NULL) {
                    RemovePalavra23(RaizArv23, Pai, Palavra, -1);
                }
            }
        } else if ((*RaizArv23)->NInfos == 2 && strcasecmp(Palavra, (*RaizArv23)->Info2->Palavra) == 0) {
            
            if (LinhaPalavra == -1) {
                if (VerificaFolha(*RaizArv23) == 1) {
                    free((*RaizArv23)->Info2);
                    (*RaizArv23)->Info2 = NULL;
                    (*RaizArv23)->NInfos = 1;
                } else {
                    Arv23 **MaiorInfoRemove = &((*RaizArv23)->center);
                    Arv23 **PaiMaior = RaizArv23;
                    RemoveMaiorInfoEsq(RaizArv23, PaiMaior, MaiorInfoRemove, 2);
                }
            } else {
                RemoveNoLinha(&((*RaizArv23)->Info2->ListaLinhas), LinhaPalavra);
                if ((*RaizArv23)->Info2->ListaLinhas == NULL) {
                    RemovePalavra23(RaizArv23, Pai, Palavra, -1);
                }    
            }
        } else if (strcasecmp(Palavra, (*RaizArv23)->Info1->Palavra) < 0) {
            RemovePalavra23(&((*RaizArv23)->esq), RaizArv23, Palavra, LinhaPalavra);
        } else if ((*RaizArv23)->NInfos == 1 || (*RaizArv23)->NInfos == 2 && strcasecmp(Palavra, (*RaizArv23)->Info2->Palavra) < 0) {
            RemovePalavra23(&((*RaizArv23)->center), RaizArv23, Palavra, LinhaPalavra);
        } else {
            RemovePalavra23(&((*RaizArv23)->dir), RaizArv23, Palavra, LinhaPalavra);
        }
    }
    RedistribuiArv23(RaizArv23, Pai);
}

void RedistribuiArv23(Arv23** RaizArv23, Arv23** Pai) {
    if (*RaizArv23 != NULL)
        if ((*RaizArv23)->NInfos == 0) {
            if (Pai != NULL) {
                if ((*RaizArv23) == ((*Pai)->dir)) {
                    if ((*Pai)->center->NInfos == 2) {
                        (*RaizArv23)->Info1 = (*Pai)->Info2;
                        (*RaizArv23)->NInfos = 1;
                        (*Pai)->Info2 = (*Pai)->center->Info2;
                        (*Pai)->center->NInfos = 1;
                        (*Pai)->center->Info2 = NULL;
                        (*RaizArv23)->esq = (*Pai)->center->dir;
                        (*Pai)->center->dir = NULL;
                    } else if ((*Pai)->center->NInfos == 1) {
                        (*RaizArv23)->Info2 = (*Pai)->Info2;
                        (*RaizArv23)->dir = (*RaizArv23)->center;
                        (*RaizArv23)->Info1 = (*Pai)->center->Info1;
                        (*RaizArv23)->NInfos = 2;
                        (*Pai)->NInfos = 1;
                        (*RaizArv23)->center = (*Pai)->center->center;
                        (*RaizArv23)->esq = (*Pai)->center->esq;
                        free((*Pai)->center);
                        (*Pai)->center = (*RaizArv23);
                        (*Pai)->dir = NULL;
                    }
                } else if ((*RaizArv23) == (*Pai)->center) {
                    if ((*Pai)->esq->NInfos == 2) {
                        (*RaizArv23)->Info1 = (*Pai)->Info1;
                        (*RaizArv23)->NInfos = 1;
                        (*Pai)->Info1 = (*Pai)->esq->Info2;
                        (*Pai)->esq->NInfos = 1;
                        (*RaizArv23)->esq = (*Pai)->esq->dir;
                        (*Pai)->esq->dir = NULL;
                    } else if ((*Pai)->esq->NInfos == 1) {
                        if ((*Pai)->NInfos == 2) {
                            (*RaizArv23)->Info2 = (*Pai)->Info1;
                            (*RaizArv23)->Info1 = (*Pai)->esq->Info1;
                            (*RaizArv23)->NInfos = 2;
                            (*RaizArv23)->dir = (*RaizArv23)->center;
                            (*RaizArv23)->center = (*Pai)->esq->center;
                            (*RaizArv23)->esq = (*Pai)->esq->esq;
                            free((*Pai)->esq);
                            (*Pai)->esq = (*RaizArv23);
                            (*Pai)->Info1 = (*Pai)->Info2;
                            (*Pai)->NInfos = 1;
                            (*Pai)->center = (*Pai)->dir;
                            (*Pai)->dir = NULL;
                        } else if ((*Pai)->NInfos == 1) {
                            (*RaizArv23)->Info2 = (*Pai)->Info1;
                            (*RaizArv23)->Info1 = (*Pai)->esq->Info1;
                            (*RaizArv23)->NInfos = 2;
                            (*Pai)->NInfos = 0;
                            (*RaizArv23)->dir = (*RaizArv23)->center;
                            (*RaizArv23)->center = (*Pai)->esq->center;
                            (*RaizArv23)->esq = (*Pai)->esq->esq;
                            free((*Pai)->esq);
                            (*Pai)->esq = NULL;
                        }
                    }
                } else if ((*RaizArv23) == (*Pai)->esq) {
                    if ((*Pai)->center->NInfos == 2) {
                        (*RaizArv23)->Info1 = (*Pai)->Info1;
                        (*RaizArv23)->NInfos = 1;
                        (*Pai)->Info1 = (*Pai)->center->Info1;
                        (*Pai)->center->NInfos = 1;
                        (*Pai)->center->Info1 = (*Pai)->center->Info2;
                        (*RaizArv23)->esq = (*RaizArv23)->center;
                        (*RaizArv23)->center = (*Pai)->center->esq;
                        (*Pai)->center->esq = (*Pai)->center->center;
                        (*Pai)->center->center = (*Pai)->center->dir;
                        (*Pai)->center->dir = NULL;
                    } else if ((*Pai)->center->NInfos == 1) {
                        if ((*Pai)->NInfos == 2) {
                            (*RaizArv23)->Info1 = (*Pai)->Info1;
                            (*RaizArv23)->Info2 = (*Pai)->center->Info1;
                            (*RaizArv23)->NInfos = 2;
                            (*RaizArv23)->esq = (*RaizArv23)->center;
                            (*RaizArv23)->center = (*Pai)->center->esq;
                            (*RaizArv23)->dir = (*Pai)->center->center;
                            (*Pai)->Info1 = (*Pai)->Info2;
                            (*Pai)->NInfos = 1;
                            free((*Pai)->center);
                            (*Pai)->center = (*Pai)->dir;
                            (*Pai)->dir = NULL;
                        } else if ((*Pai)->NInfos == 1) {
                            (*RaizArv23)->Info1 = (*Pai)->Info1;
                            (*RaizArv23)->esq = (*RaizArv23)->center;
                            (*RaizArv23)->Info2 = (*Pai)->center->Info1;
                            (*RaizArv23)->center = (*Pai)->center->esq;
                            (*RaizArv23)->dir = (*Pai)->center->center;
                            (*Pai)->NInfos = 0;
                            (*RaizArv23)->NInfos = 2;
                            free((*Pai)->center);
                            (*Pai)->center = (*RaizArv23);
                            (*Pai)->esq = NULL;
                        }
                    }
                }
            } else if (Pai == NULL) {
                (*RaizArv23) = (*RaizArv23)->center;
            }  
        }
}