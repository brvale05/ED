#ifndef FILA_H
#define FILA_H

typedef struct Fila Fila;

Fila *FilaConstruct();

void FilaDestroy(Fila *f);

void FilaPushBack(Fila *f, int codigo);

void FilaRemove(Fila *f);

void FilaPrint(Fila *f);

#endif