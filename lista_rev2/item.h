#ifndef ITEM_H
#define ITEM_H
#include "produto.h"

typedef struct Item Item;

Item* CriaItem(int qtd, Produto *p);

void LiberaItem(Item *i);

char* GetNomeItem(Item *i);

float GetValorItem(Item *i);

int GetQuantidadeItem(Item *i);

Item* LeItem();

void ImprimeItem(Item *i);

#endif
