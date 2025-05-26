#ifndef LISTA_H
#define LISTA_H
#include "produto.h"

typedef struct Lista Lista;

typedef struct Celula Celula;

Lista *CriaLista();

void InsereLista(Lista *l, Produto *prod);

void RetiraLista(Lista *l, int codigo);

int EhListaVazia(Lista *l);

void DesalocaLista(Lista *l);

void ImprimeLista(Lista *l);

#endif