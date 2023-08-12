typedef struct grafo *Grafo;

Grafo inicializaGrafo(int n);
void insereArcoGrafo(Grafo G, int v, int w);
void insereArcoNaoSeguraGrafo(Grafo G, int v, int w);
void removeArcoGrafo(Grafo G, int v, int w);
void mostraGrafo(Grafo G);
void imprimeGrafo(Grafo G);