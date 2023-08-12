#include <stdio.h>
#include <stdlib.h>
#include "ImpGrafo.h"

int main(){
    Grafo G = inicializaGrafo(5);
    insereArcoGrafo(G, 0, 1);
    insereArcoGrafo(G, 0, 2);
    insereArcoGrafo(G, 0, 3);
    insereArcoGrafo(G, 1, 2);
    insereArcoGrafo(G, 1, 3);
    insereArcoGrafo(G, 2, 3);
    insereArcoGrafo(G, 2, 4);
    insereArcoGrafo(G, 3, 4);
    mostraGrafo(G);
    printf("\n");
    removeArcoGrafo(G, 0, 1);
    mostraGrafo(G);
    printf("\n");
    return 0;
}