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

void *ListSearch(Lista *list, void *id, fptr_compare compara)
{
    Celula *atual = list->inicio;

    while (atual != NULL)
    {
        if (compara(atual->data, id))
        {
            return atual->data;
        }
        atual = atual->prox;
    }

    return NULL;
}

void *ListRemove(Lista *list, fptr_compare compara, void *id)
{
    Celula *antes = NULL;
    Celula *atual = list->inicio;

    while (atual != NULL)
    {
        if (compara(atual->data, id))
        {
            break;
        }
        antes = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
        return NULL;

    void *data = atual->data;

    if (list->inicio == atual && list->fim == atual)
    {
        list->inicio = list->fim = NULL;
        free(atual);
        return data;
    }

    if (atual == list->fim)
    {
        list->fim = antes;
        list->fim->prox = NULL;
       
        free(atual);
        return data;
    }

    if (atual == list->inicio)
    {
        list->inicio = list->inicio->prox;
        free(atual);
    }
    else
    {
        antes = atual->prox;
        free(atual);
    }

    return data;
}

void StrDestroy(void *data)
{
    if (((char *)data))
    {
        free(((char *)data));
    }
}

void ListPrint(Lista *list, fptr_print imprime, FILE *stdout_f)
{
    Celula *atual = list->inicio;

    while (atual != NULL)
    {
        imprime(atual->data, stdout_f);
        atual = atual->prox;
    }
}

void StrPrint(void *data)
{
    printf(";%s", ((char *)data));
}

int StrCompare(void *a, void *b)
{
    char *gen1 = (char*)a;
    char *gen2 = (char*)b;

    if(!strcmp(gen1, gen2))
    return 1;

    return 0;
}

int GetListSize(Lista *list)
{
    return list->tam;
}

void *GetDataCell(Celula *c)
{
    return c->data;
}

Celula *GetFirstCell(Lista *l)
{
    return l->inicio;
}
