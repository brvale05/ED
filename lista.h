#ifndef LISTA_H
#define LISTA_H

typedef struct Lista Lista;

typedef struct Celula Celula;

typedef void (*fptr_print)(void *data);

typedef void (*fptr_destroy)(void *data);

typedef int (*fptr_compare)(void *dado, int id);

Lista *ListConstruct();

void ListPushBack(Lista *list, void *data);

void ListDestroy(Lista *list, int libera_flag, fptr_destroy destroy);

void* ListSearch(Lista *list, int id, fptr_compare compara);

void StrDestroy(void *data);

void ListPrint(Lista *list, fptr_print imprime);

void StrPrint(void *data);

#endif