#ifndef LISTA_H
#define LISTA_H

typedef struct Lista Lista;

typedef struct Celula Celula;

typedef void (*fptr_print)(void *data);

typedef void (*fptr_destroy)(void *data);

// typedef int (*funct_ptr_compara)(void *dado, int id);

Lista *ListConstruct();

void ListPushBack(Lista *list, void *data);

void ListDestroy(Lista *list, fptr_destroy destroy);

void CharDestroy(void *data);

void ListPrint(Lista *list, fptr_print imprime);

void CharPrint(void *data);

#endif