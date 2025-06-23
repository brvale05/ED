#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool encontrado = false;

struct Grafo
{
    int n_vertices;
    int grau_max;
    int **arestas;
    int *grau;
};

Grafo *GrafoConstruct(int qtdvertices, int grau_max)
{
    Grafo *g = malloc(sizeof(Grafo));

    g->n_vertices = qtdvertices;
    g->grau_max = grau_max;

    int i;

    g->grau = calloc(qtdvertices, sizeof(int));
    g->arestas = malloc(sizeof(int*)*qtdvertices);

    for(i = 0; i < qtdvertices; i++)
    {
       g->arestas[i] = malloc(grau_max * sizeof(int));
    }

    return g;
    
}

void GrafoDestroy(Grafo *g)
{
    if(g)
    {
        if(g->grau)
        free(g->grau);

        if(g->arestas)
        {
            int i;
            for(i = 0; i < g->n_vertices; i++)
            {
                if(g->arestas[i])
                free(g->arestas[i]);
            }

            free(g->arestas);
        }
        
        free(g);
    }
}

void GrafoPushBack(Grafo *g, int id_origem, int id_destino, int eh_digrafo)
{
    g->arestas[id_origem][g->grau[id_origem]] = id_destino;
    g->grau[id_origem]++;

    if(!eh_digrafo)
    GrafoPushBack(g, id_origem, id_destino, 1);

    return;
}

int GrafoSearch(Grafo *gr, int id_origem, int id_alvo, int *visitado)
{
    int i, count = 1;

    for(i = 0; i < gr->n_vertices; i++)
    {
        visitado[i] = 0;
    }

    return SearchProfundidade(gr, id_origem, id_alvo, visitado, 1);
}

int SearchProfundidade(Grafo *gr, int id_origem, int id_alvo, int *visitado, int count)
{
    if(encontrado = true)
    {
        return 1;
    }

    int i;
    visitado[id_origem] = count;

    for(i = 0; i < gr->grau[id_origem]; i++)
    {
        if(gr->arestas[id_origem][i] == id_alvo)
        {
            encontrado = true;
            return 1;
        }

        if(!visitado[gr->arestas[id_origem][i]])
        {
            return SearchProfundidade(gr, gr->arestas[id_origem][i], id_alvo, visitado, count++);
        }
    }

    return 0;
}
