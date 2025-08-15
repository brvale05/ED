#ifndef MAPA_DE_CODIFICACAO
#define MAPA_DE_CODIFICACAO

#define TAM_MAX_MAPA 256

#include "codigohuffman.h"
#include "arvore.h"
#include "bitmap.h"
#include "utils.h"

typedef struct MapaCodificacao MapaCodificacao;

MapaCodificacao *MapaCodificacaoConstruct(int tam);

void MapPushBack(MapaCodificacao *map, CodigoHuffman *item_map, unsigned int id);

void MapDestroy(MapaCodificacao *map);

void BinaryCodeConstruct(Arvore *raiz, char *codigo, int id_profundidade, MapaCodificacao *map, unsigned int *array_de_frequencias, unsigned int *qtd_bits);

void BitMapCompacta(MapaCodificacao *decodifica_map, char *caminho, bitmap *map);

void BinaryCodeDescompacta(Arvore *raiz, char *codigo, int id_profundidade, MapaCodificacao *map);

void OriginalFileReconstruct(Arvore *raiz, bitmap *bm, char *caminho);

void OriginalFileReconstruct_Aux(Arvore *raiz, int *flag, FILE *output_file);

#endif