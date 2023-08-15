#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 1000

typedef struct {
    int vertice;
    double confiabilidade;
} Aresta;

typedef struct {
    Aresta *arestas;
    int num_arestas;
} Grafo;

typedef struct {
    double confiabilidade;
    int vertice;
} FilaPrioridade;

void dijkstra(const Grafo *grafo, int origem, int destino, int num_vertices) {
    bool *visitados = (bool *)malloc(num_vertices * sizeof(bool));
    double *confiabilidade = (double *)malloc(num_vertices * sizeof(double));
    for (int i = 0; i < num_vertices; ++i) {
        visitados[i] = false;
        confiabilidade[i] = 0.0;
    }
    confiabilidade[origem] = 1.0;

    FilaPrioridade *fp = (FilaPrioridade *)malloc(num_vertices * sizeof(FilaPrioridade));
    int tamanho_fp = 0;
    fp[tamanho_fp++] = (FilaPrioridade){1.0, origem};

    while (tamanho_fp > 0) {
        FilaPrioridade min_confiab = fp[0];
        int min_idx = 0;
        for (int i = 1; i < tamanho_fp; ++i) {
            if (fp[i].confiabilidade > min_confiab.confiabilidade) {
                min_confiab = fp[i];
                min_idx = i;
            }
        }

        fp[min_idx] = fp[--tamanho_fp];
        visitados[min_confiab.vertice] = true;

        if (min_confiab.vertice == destino) {
            printf("O caminho mais confiável entre %d e %d tem confiabilidade %.4lf\n",
                   origem, destino, min_confiab.confiabilidade);
            free(visitados);
            free(confiabilidade);
            free(fp);
            return;
        }

        for (int i = 0; i < grafo[min_confiab.vertice].num_arestas; ++i) {
            Aresta aresta = grafo[min_confiab.vertice].arestas[i];
            if (!visitados[aresta.vertice]) {
                double nova_confiab = min_confiab.confiabilidade * aresta.confiabilidade;
                if (nova_confiab > confiabilidade[aresta.vertice]) {
                    confiabilidade[aresta.vertice] = nova_confiab;
                    fp[tamanho_fp++] = (FilaPrioridade){nova_confiab, aresta.vertice};
                }
            }
        }
    }

    printf("Não há caminho confiável entre %d e %d\n", origem, destino);
    free(visitados);
    free(confiabilidade);
    free(fp);
}

int main() {
    FILE *arquivo = fopen("../grafo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int num_vertices, num_arestas;
    fscanf(arquivo, "%d %d", &num_vertices, &num_arestas);

    Grafo *grafo = (Grafo *)malloc(num_vertices * sizeof(Grafo));
    for (int i = 0; i < num_vertices; ++i) {
        grafo[i].num_arestas = 0;
        grafo[i].arestas = NULL;
    }

    for (int i = 0; i < num_arestas; ++i) {
        int u, v;
        double confiabilidade;
        fscanf(arquivo, "%d %d %lf", &u, &v, &confiabilidade);
        
        grafo[u].arestas = (Aresta *)realloc(grafo[u].arestas, (grafo[u].num_arestas + 1) * sizeof(Aresta));
        grafo[u].arestas[grafo[u].num_arestas++] = (Aresta){v, confiabilidade};
    }

    int origem, destino;
    printf("Digite o vértice de origem e o vértice de destino: ");
    scanf("%d %d", &origem, &destino);

    dijkstra(grafo, origem, destino, num_vertices);

    for (int i = 0; i < num_vertices; ++i) {
        free(grafo[i].arestas);
    }
    free(grafo);

    fclose(arquivo);

    return 0;
}