#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>

typedef struct Lista Lista;

typedef struct Celula Celula;

struct Celula
{
    Celula *prox;
    void *data;
};

typedef void (*fptr_print)(void *data, FILE *stdout_f);

typedef void (*fptr_destroy)(void *data);

typedef int (*fptr_compare)(void *dado, void *id);

Lista *ListConstruct();

void ListPushBack(Lista *list, void *data);

void ListDestroy(Lista *list, int libera_flag, fptr_destroy destroy);

void* ListSearch(Lista *list, void *id, fptr_compare compara);

void *ListRemove(Lista *list, fptr_compare compara, void *id);

void StrDestroy(void *data);

int StrCompare(void *a, void *b);

void ListPrint(Lista *list, fptr_print imprime, FILE *stdout_f);

void StrPrint(void *data);

int GetListSize(Lista *list);

void *GetDataCell(Celula *c);

Celula *GetFirstCell(Lista *l);

#endif