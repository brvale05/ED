#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Lista
{
    Lista *prox;
    Lista *ant;
    Produto *item;
    int tam;
};

Lista *CriaLista()
{
    return NULL;
}

Lista *InsereLista(Lista *l, Produto *prod)
{
    Lista *novo = malloc(sizeof(Lista));

    novo->prox = l;
    novo->ant = NULL;
    novo->item = prod;

    if(l != NULL)
    {
        l->ant = novo;
    }

    return novo;
}

Lista *Busca(Lista *l, int codigo)
{
    Lista *aux;

    for (aux = l; aux != NULL; aux = aux->prox)
    {
        if(GetCodigoProduto(aux->item) == codigo)
        return aux;
    }

    return NULL;
    
}

Lista *RetiraLista(Lista *l, int codigo)
{
    Lista *atual = Busca(l, codigo);

    if(l == NULL) //lista vazia
    return l;

    if(atual == NULL) //nao encontrou o item
    return l;

    if(l == atual) //primeiro elemento
    {
        l = atual->prox;
        LiberaProduto(atual->item);
        free(atual);
        return l;
    }
    
    if(atual->prox == NULL) //testa se eh o ultimo elemento
    {
        atual->ant->prox = NULL;
        LiberaProduto(atual->item);
        free(atual);
        return l;
    }

    atual->ant->prox = atual->prox;

    LiberaProduto(atual->item);
    free(atual);

    return l;
}

int EhListaVazia(Lista *l)
{
    if (l == NULL)
    {
        return 1;
    }
    return 0;
}

void DesalocaLista(Lista *l)
{
    Lista *antes = NULL;
    Lista *atual = l;

    if (l)
    {
        while (atual != NULL)
        {
            antes = atual;
            atual = atual->prox;
            LiberaProduto(antes->item);
            free(antes);
        }
    }
}

void ImprimeLista(Lista *l)
{
    printf("\n");
    printf("LISTA DE PRODUTOS:\n");

    Lista *aux;
    aux = l;

    while (aux != NULL)
    {
        ImprimeProduto(aux->item);
        aux = aux->prox;
        printf("\n");
    }
}
