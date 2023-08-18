#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"

typedef struct VerticeGrafo {
    int posVertice;
    int Pinos;
    int arcos[3];
} Vertice;

void preencherVertices(Vertice *ListaAdjVertices[]) {
    FILE *file = fopen("configs_Torre_Hanoi.csv", "r");

    int i = 0;
    char linha[100];

    while (fgets(linha, sizeof(linha), file)) {
        int posVertice, Pinos;
        char arcos_str[10];
        ListaAdjVertices[i] = (Vertice *)malloc(sizeof(Vertice));

        sscanf(linha, "%d,%d,\"%9[^\"]\"\n", &posVertice, &Pinos, arcos_str);

        ListaAdjVertices[i]->posVertice = posVertice;
        ListaAdjVertices[i]->Pinos = Pinos;\

        char *token = strtok(arcos_str, ",");
        int j = 0;
        while (token != NULL && j < 3) {
            ListaAdjVertices[i]->arcos[j] = atoi(token);
            token = strtok(NULL, ",");
            j++;
        }
        while (j < 3) {
            ListaAdjVertices[i]->arcos[j] = -1;
            j++;
        }
        i++;
    }

    fclose(file);

}

void imprimeVetor(Vertice *ListaAdjVertices[]) {
    for(int i = 0; i < QntVertices; i++) {
        printf("Vertice: %d\nPinos: %d\n", ListaAdjVertices[i]->posVertice, ListaAdjVertices[i]->Pinos);
        printf("arcos: ");

        int j; j = 0;
        while (j < 3 && ListaAdjVertices[i]->arcos[j] != -1) {
            printf("%d ", ListaAdjVertices[i]->arcos[j]);
            j++;
        }
        printf("\n\n");
    }
}

void preencherMatriz(Vertice *ListaAdjVertices[], int MatrizAdj[][QntVertices]) {
    for (int origem = 0; origem < QntVertices; origem++) {
        for (int destino = 0; destino < QntVertices; destino++) {
            MatrizAdj[origem][destino] = temArco(ListaAdjVertices[origem], destino + 1);
        }
    }
}

int temArco(Vertice *vertice, int destino) {
    for (int i = 0; i < 3; i++) {
        if (vertice->arcos[i] == destino) {
            return 1;
        }
    }
    return 0;
}

void imprimeMatriz(int MatrizAdj[][QntVertices]) {
    int i, j;

    for (i = 0; i < QntVertices; i++) {
        for (j = 0; j < QntVertices; j++) {
            printf("%d ", MatrizAdj[i][j]);
        }
        printf("\n");
    }
}

void encontrarMenorCaminho(int MatrizAdj[][QntVertices]) {
    int origem;
    int destino = QntVertices - 1;

    
    clock_t start_time, end_time;
    double timeDij, timeBell;
    
    for(int i=0; i < 50; i++){
        origem = rand() % 81;
        start_time = clock();
        algoDijkstra(MatrizAdj, origem, destino);
        end_time = clock();
        timeDij += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }

    printf("Dijkstra: %lf ms\n", (timeDij * 1000)/50);

    
    for(int i=0; i < 50; i++){
        origem = rand() % 81;
        start_time = clock();
        algoBellmanFord(MatrizAdj, origem, destino);
        end_time = clock();
        timeBell += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }
    printf("Bellman: %lf ms\n", (timeBell * 1000)/50);
}

void algoDijkstra(int MatrizAdj[][QntVertices], int origem, int destino) {
    int distancias[QntVertices];
    int visitados[QntVertices];

    for (int i = 0; i < QntVertices; i++) {
        distancias[i] = inf;
        visitados[i] = 0;
    }

    distancias[origem] = 0;

    for (int contador = 0; contador < QntVertices - 1; contador++) {
        int verticeAtual = -1;

        for (int i = 0; i < QntVertices; i++) {
            if (!visitados[i] && (verticeAtual == -1 || distancias[i] < distancias[verticeAtual])) {
                verticeAtual = i;
            }
        }

        visitados[verticeAtual] = 1;

        for (int v = 0; v < QntVertices; v++) {
            if (!visitados[v] && MatrizAdj[verticeAtual][v] && distancias[verticeAtual] != inf &&
                distancias[verticeAtual] + MatrizAdj[verticeAtual][v] < distancias[v]) {
                distancias[v] = distancias[verticeAtual] + MatrizAdj[verticeAtual][v];
            }
        }
    }

    printf("Menor caminho de %d para %d: %d\n", origem, destino, distancias[destino]);
}


void algoBellmanFord(int MatrizAdj[][QntVertices], int origem, int destino) {
    int distancias[QntVertices];

    for (int i = 0; i < QntVertices; i++) {
        distancias[i] = inf;
    }

    distancias[origem] = 0;

    for (int etapa = 0; etapa < QntVertices - 1; etapa++) {
        for (int u = 0; u < QntVertices; u++) {
            for (int v = 0; v < QntVertices; v++) {
                if (MatrizAdj[u][v] && distancias[u] != inf &&
                    distancias[u] + MatrizAdj[u][v] < distancias[v]) {
                    distancias[v] = distancias[u] + MatrizAdj[u][v];
                }
            }
        }
    }

    printf("Menor caminho de %d para %d: %d\n", origem, destino, distancias[destino]);
}
