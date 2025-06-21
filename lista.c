#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Lista
{
    Celula *inicio;
    Celula *fim;
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
            if(libera_flag)
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
