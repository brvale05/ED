#ifndef PILHA_H
#define PILHA_H
#define TAM_MAX 6

typedef struct Pilha Pilha;

Pilha *PilhaConstruct();

void PilhaDestroy(Pilha *p);

void PilhaPush1(Pilha *p, int codigo);

void PilhaPush2(Pilha *p, int codigo);

void PilhaRemove1(Pilha *p);

void PilhaRemove2(Pilha *p);

void PilhaPrint(Pilha *p);

int Cheia(Pilha *p);

#endif