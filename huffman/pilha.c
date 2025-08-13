#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct Pilha
{
    Arvore **trees;
    int topo;
};

Pilha *PilhaConstruct()
{
    Pilha *p = malloc(sizeof(Pilha));
    p->topo = 0;

    p->trees = calloc(TAM_MAX, sizeof(Arvore *));

    return p;
}

void PilhaDestroy(Pilha *p)
{
    if (p)
    {
        if (p->trees)
        {
            free(p->trees);
        }
        free(p);
    }
}

void PilhaPush(Pilha *p, Arvore *arv)
{
    if (!Cheia(p))
    {
        p->trees[p->topo] = arv;
        p->topo++;
    }
}

void PilhaPrint(Pilha *p)
{
    for (int i = 0; i < p->topo; i++)
    {
        TreePrint(p->trees[i]);
    }
}

void OrdenaPilha(Pilha *p)
{
    qsort(p->trees, p->topo, sizeof(Arvore *), TreesCompare);
}

void PilhaVectorUpdate(Pilha *p, unsigned int *array)
{
    for (int i = 0; i < TAM_MAX; i++)
    {
        if (array[i] > 0)
        {
            PilhaPush(p, TreeConstruct(i, array[i], EH_FOLHA));
        }
    }
}

Arvore *BinaryTreeConstruct(Pilha *p)
{
    Arvore *root, *aux;

    int i = 0;
    while (1)
    {
        root = TreePushBack(p->trees[i], p->trees[i + 1]);

        p->trees[i] = root;

        if (p->topo == 2)
        {
            p->topo = 1;
            break;
        }

        aux = p->trees[i + 1];
        p->trees[i + 1] = p->trees[p->topo - 1];
        p->trees[p->topo - 1] = aux;

        p->topo--;

        OrdenaPilha(p);
    }

    return root;
}

int Cheia(Pilha *p)
{
    if (p->topo == TAM_MAX - 1)
    {
        printf("Pilha Cheia!\n");
        return 1;
    }

    return 0;
}