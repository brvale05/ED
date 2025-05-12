#ifndef FILIAL_H
#define FILIAL_H
#include "estoque.h"

typedef struct Filial Filial;

Filial *CriaFilial(char *nome);

void LiberaFilial(Filial *f);

void AtribuiEstoque(Filial *f, Estoque *e);

Filial *LeFilial();

float CalculaValorEstoqueFilial(Filial *f);

void ImprimeFilial(Filial *f);

#endif