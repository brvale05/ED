#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Lista
{
    Celula *inicio;
    Celula *fim;
    int tam;
};

struct Celula
{
    Celula *prox;
    Produto *item;
};

Lista *CriaLista()
{
    Lista *l = malloc(sizeof(Lista));

    l->tam = 0;
    l->inicio = NULL;
    l->fim = NULL;

    return l;
}

void InsereLista(Lista *l, Produto *prod)
{
    Celula *novo = calloc(sizeof(Celula), 1);

    if (l->fim == NULL)
    {
        novo->item = prod;
        l->inicio = l->fim = novo;
    }
    else
    {
        l->fim->prox = novo;
        l->fim = l->fim->prox;
        l->fim->item = prod;
        l->fim->prox = NULL;
    }

    l->tam++;
}

void RetiraLista(Lista *l, int codigo)
{
    Celula *antes = NULL;
    Celula *atual = l->inicio;

    while (atual != NULL && GetCodigoProduto(atual->item) != codigo)
    {
        antes = atual;
        atual = atual->prox;
    }

    if (EhListaVazia(l))
        return;

    if (atual == l->inicio && atual == l->fim)
    {
        LiberaProduto(atual->item);

        l->inicio = l->fim = NULL;

        free(atual);
        return;
    }

    if (atual == l->fim)
    {
        l->fim = antes;
        l->fim->prox = NULL;
        LiberaProduto(atual->item);
        free(atual);
        return;
    }

    if (atual == l->inicio)
    {
        l->inicio = l->inicio->prox;
        LiberaProduto(atual->item);
        free(atual);
    }
    else
    {
        antes = atual->prox;
        LiberaProduto(atual->item);
        free(atual);
    }
}

int EhListaVazia(Lista *l)
{
    if (l->inicio == NULL)
    {
        return 1;
    }
    return 0;
}

void DesalocaLista(Lista *l)
{
    Celula *antes = NULL;
    Celula *atual = l->inicio;

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

    free(l);
}

void ImprimeLista(Lista *l)
{
    printf("LISTA DE PRODUTOS:\n");

    Celula *aux;
    aux = l->inicio;

    while (aux != NULL)
    {
        ImprimeProduto(aux->item);
        aux = aux->prox;
    }
}
