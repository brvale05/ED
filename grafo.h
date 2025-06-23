#ifndef GRAFOS_H
#define GRAFOS_H

typedef struct Grafo Grafo;

Grafo *GrafoConstruct(int qtdvertices, int grau_max);

void GrafoDestroy(Grafo *g);

void GrafoPushBack(Grafo *g, int id_origem, int id_destino, int eh_digrafo);

int GrafoSearch(Grafo *gr, int id_origem, int id_alvo, int *visitado);

int SearchProfundidade(Grafo *gr, int id_origem, int id_alvo, int *visitado, int count);

#endif