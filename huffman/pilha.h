#ifndef PILHA_H
#define PILHA_H
#define TAM_MAX 1000

#include "arvore.h"

typedef struct Pilha Pilha;

Pilha *PilhaConstruct();

void PilhaDestroy(Pilha *p);

void PilhaPush(Pilha *p, Arvore *arv);

//void PilhaPrint(Pilha *p);

void OrdenaPilha(Pilha *p);

void PilhaVectorUpdate(Pilha *p, int *array);   

Arvore *BinaryTreeConstruct(Pilha *p);

int Cheia(Pilha *p);

#endif