#ifndef SUPERMERCADO_H
#define SUPERMERCADO_H
#include "filial.h"

typedef struct Supermercado Supermercado;

Supermercado *CriaSupermercado(char *nome);

void LiberaSupermercado(Supermercado *s);

void AtribuiFilial(Supermercado *s, Filial *data);

Filial *GetFilial(Supermercado *s, int i);

float GetValorTotalEstoques(Supermercado *s);

void CalculaValorTotalSup(Supermercado *s);

void ImprimeSupermercado(Supermercado *s);

#endif