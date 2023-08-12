#include <stdio.h>
#include <stdlib.h>
#include "ImpGrafo.h"

struct grafo{
    int **A;
    int n;
    int m;
};

Grafo inicializaGrafo(int n){
    int i, j;

    Grafo G = malloc(sizeof(*G));
    G->n = n;
    G->m = 0;
    G->A = malloc(n * sizeof(int *));
    for(i = 0; i < n; i++){
        G->A[i] = malloc(n * sizeof(int));
    }
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            G->A[i][j] = 0;
        }
    }
    return G;
}



/* Insere arco  v-w no grafo G, supondo que v e w são inteiros distintos entre 0 e n-1. Se grafo já tem arco v-w, não faz nada.*/
void insereArcoGrafo(Grafo G, int v, int w){
    if(G->A[v][w] == 0){
        G->A[v][w] = 1;
        G->m++;
    }
}

//Versão da insereArcoGrafo() que não testa se v-w já está presente

void insereArcoNaoSeguraGrafo(Grafo G, int v, int w){
    G->A[v][w] = 1;
    G->m++;
}

/* Remove arco v-w do grafo G, supondo que v e w são inteiros distintos entre 0 e n-1. Se não existe arco v-w, não faz nada.*/

void removeArcoGrafo(Grafo G, int v, int w){
    if(G->A[v][w] == 1){
        G->A[v][w] = 0;
        G->m--;
    }
}

//Imprime, para vérticie v, os vérticies adjacentes a v.
void mostraGrafo(Grafo G){
    int i,j;
    for(i = 0; i < G->n;i++){ //Para cada Vérticie
        printf("%2d: ", i);
        for(j =0; j < G->n; j++){ //Todos os possiveis visinhos
            if(G->A[i][j]==1){ //Mas só se for visinho
                printf(" %2d", j);
            }
        }
        printf("\n");
    }
}

//Versão da mostraGrafo() com impressão mais Limpa
void imprimeGrafo(Grafo G){
    int i,j;
    for(i = 0; i < G->n; j++){
        for (int j = 0; j < G->n; j++){
            if(G->A[i][j] == 1){
                printf("%2d", j);
            }
        }
        printf("-1");
        printf("\n");
    }
}

//Libera a memória alocada para o grafo G e devolver NULL.

Grafo LiberaGrafo(Grafo G){
    int i;
    for(i = 0; i<G->n; i++){
        free(G->A[i]);
        G->A[i]= NULL;
    }
    free(G->A);
    G->A = NULL;
    free(G);
    return NULL;    
}