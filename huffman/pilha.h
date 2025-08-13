#ifndef PILHA_H
#define PILHA_H
#define TAM_MAX 256

#include "arvore.h"

typedef struct Pilha Pilha;

Pilha *PilhaConstruct();

void PilhaDestroy(Pilha *p);

void PilhaPush(Pilha *p, Arvore *arv);

void PilhaPrint(Pilha *p);

void OrdenaPilha(Pilha *p);

void PilhaVectorUpdate(Pilha *p, unsigned int *array);

Arvore *BinaryTreeConstruct(Pilha *p);

int Cheia(Pilha *p);

#endif