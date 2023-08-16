#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "grafo.h"

int main() {    
    Vertice *ListaVertices[QntVertices];
    int MatAdjacencia[QntVertices][QntVertices];

    preencherVertices(ListaVertices);
    preencherMatriz(ListaVertices, MatAdjacencia);
    encontrarMenorCaminho(MatAdjacencia);

    return 0;
}