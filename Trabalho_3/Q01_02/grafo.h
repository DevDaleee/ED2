#define QntVertices 81
#define inf 1000000

typedef struct VerticeGrafo Vertice;

void preencherVertices(Vertice *ListaAdjVertices[]);
int temArco(Vertice *vertice, int destino);
void imprimeVetor(Vertice *ListaAdjVertices[]);
void preencherMatriz(Vertice *ListaAdjVertices[], int MatrizAdj[][QntVertices]);
void imprimeMatriz(int MatrizAdj[][QntVertices]);
void encontrarMenorCaminho(int MatrizAdj[][QntVertices]);
void algoDijkstra(int MatrizAdj[][QntVertices], int inicio, int destino);
void algoBellmanFord(int MatrizAdj[][QntVertices], int inicio, int destino);