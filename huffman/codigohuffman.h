#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

#include "bitmap.h"

typedef struct CodigoHuffman CodigoHuffman;

CodigoHuffman *CodigoHuffmanConstruct(char *code, int tam, unsigned char car);

// CodigoHuffman **TableVectorConstruct(int tam);

// void VectorPushBack(CodigoHuffman **vector, CodigoHuffman *data, int id);

void CodigoHuffmanDestroy(CodigoHuffman *t);

// void TableVectorDestroy(CodigoHuffman **vector);

// void PrintTable(CodigoHuffman **vector);

// void BinaryCodeConstruct(Arvore *raiz, char *codigo, int id_profundidade, CodigoHuffman **vector, unsigned int *array_de_frequencias, unsigned int *qtd_bits);

// void UpdateMapaDeBits(CodigoHuffman **vector, char *caminho, bitmap *map);

void WriteFileCompactado(bitmap *map, bitmap *tree_map, unsigned int qtdbits_map, unsigned int qtdbits_treemap, char *caminho);

// void BinaryCodeDescompacta(Arvore *raiz, char *codigo, int id_profundidade, CodigoHuffman **vector);

int GetTamHuffmanCode(CodigoHuffman *h);

char GetBitHuffmanCode(CodigoHuffman *h, int id);

#endif