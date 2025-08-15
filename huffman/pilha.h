#ifndef PILHA_H
#define PILHA_H
#define TAM_MAX_PILHA 10000

#include "arvore.h"

typedef struct Pilha Pilha;

Pilha *PilhaConstruct();

void PilhaDestroy(Pilha *p);

void PilhaPush(Pilha *p, Arvore *arv);

void PilhaPrint(Pilha *p);

void OrdenaPilha(Pilha *p);

void PilhaPushBack(Pilha *p, unsigned int *array);

Arvore *HuffmanTreeConstruct(Pilha *p);

int Cheia(Pilha *p);

#endif