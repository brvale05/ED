#ifndef LISTA_H
#define LISTA_H
#include "produto.h"

typedef struct Lista Lista;

typedef struct Celula Celula;

Lista *CriaLista();

Lista *InsereLista(Lista *l, Produto *prod);

Lista *Busca(Lista *l, int codigo);

Lista *RetiraLista(Lista *l, int codigo);

int EhListaVazia(Lista *l);

void DesalocaLista(Lista *l);

void ImprimeLista(Lista *l);

#endif