#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

#include "bitmap.h"
#include "arvore.h"
#include "utils.h"

typedef struct Tabela Tabela;

Tabela *TabelaConstruct(char *code, int code_size, char car);

Tabela **TableVectorConstruct(int tam);

void VectorPushBack(Tabela **vector, Tabela *data, int id);

void TableDestroy(Tabela *t);

void TableVectorDestroy(Tabela **vector);

void PrintTable(Tabela **vector);

void BinaryCodeConstruct(Arvore *raiz, char *codigo, int id_profundidade, Tabela **vector, unsigned int *array_de_frequencias, unsigned int *qtd_bits);

void UpdateMapaDeBits(Tabela **vector, char *caminho, bitmap *map);

void BinaryFileWrite(bitmap *map, bitmap *tree_map, unsigned int qtdbits_map, unsigned int qtdbits_treemap, char *caminho);

void BinaryCodeDescompacta(Arvore *raiz, char *codigo, int id_profundidade, Tabela **vector);

#endif