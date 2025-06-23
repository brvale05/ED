#include "lista.h"
#include "leitor.h"
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
    void *data;
};

Lista *ListConstruct()
{
    Lista *l = calloc(1, sizeof(Lista));

    l->inicio = NULL;
    l->fim = NULL;
    l->tam = 0;

    return l;
}

void ListPushBack(Lista *list, void *data)
{
    Celula *novo = malloc(sizeof(Celula));

    if (list->fim == NULL)
    {
        list->inicio = list->fim = novo;
        list->fim->data = data;
        list->fim->prox = NULL;
    }
    else
    {
        list->fim->prox = novo;
        list->fim = list->fim->prox;
        list->fim->data = data;
        list->fim->prox = NULL;
    }

    list->tam++;
}

void ListDestroy(Lista *list, int libera_flag, fptr_destroy destroy)
{
    Celula *antes = NULL;
    Celula *atual = list->inicio;

    if (list)
    {
        while (atual != NULL)
        {
            antes = atual;
            atual = atual->prox;
            if (libera_flag)
                destroy(antes->data);
            free(antes);
        }

        free(list);
    }
}

void *ListSearch(Lista *list, int id, fptr_compare compara)
{
    Celula *antes = NULL;
    Celula *atual = list->inicio;

    while (atual != NULL && !compara(atual->data, id))
    {
        antes = atual;
        atual = atual->prox;
    }

    return atual->data;
}

void StrDestroy(void *data)
{
    if (((char *)data))
    {
        free(((char *)data));
    }
}

void ListPrint(Lista *list, fptr_print imprime)
{
    Celula *antes = NULL;
    Celula *atual = list->inicio;

    while (atual != NULL)
    {
        imprime(atual->data);
        atual = atual->prox;
    }
}

void StrPrint(void *data)
{
    printf(";%s", ((char *)data));
}

int StrCompare(const void *a, const void *b)
{
    return strcmp(((char*)a), ((char*)b));
}

int GetListSize(Lista *list)
{
    return list->tam;
}

void *GetDataCel(Celula *c)
{
    return c->data;
}

int ListCompare(Lista *l1, Lista *l2, int (*compare)(const void *, const void *))
{
    Celula *c1 = l1->inicio;
    Celula *c2 = l2->inicio;

    while (c1 != NULL)
    {
        if (CellCompare(c1, c2, compare))
        {
            return 1;
        }
        c1 = c1->prox;
    }

    return 0;
}

int CellCompare(Celula *c1, Celula *c2, int (*compare)(const void *, const void *))
{
    while (c2 != NULL)
    {
        if (!compare(GetDataCel(c1), GetDataCel(c2)))
        {
            return 1;
        }
        c2 = c2->prox;
    }

    return 0;
}

void UpdateAfinidade(Lista *readers_list)
{
    Celula *c1 = readers_list->inicio;
    Celula *c2 = readers_list->inicio->prox;

    while (1)
    {
        while (c1 != NULL)
        {
            if (ListCompare(GetPrefList(GetDataCel(c1)), GetPrefList(GetDataCel(c2)), StrCompare))
            {

            }
            c1 = c1->prox;
        }
    }
}