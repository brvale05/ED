#ifndef ESTOQUE_H
#define ESTOQUE_H
#include "item.h"

typedef struct Estoque Estoque;

Estoque *CriaEstoque();

void LiberaEstoque(Estoque *e);

void AtribuiItemEstoque(Estoque *e, Item *item);

Item *GetItemEstoque(Estoque *e, int i);

int GetEstoqueTamanho(Estoque *e);

Estoque *LeEstoque();

float CalculaEstoque(Estoque *e);

void ImprimeEstoque(Estoque *e);

#endif
