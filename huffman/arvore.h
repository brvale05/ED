#ifndef ARVORE_H
#define ARVORE_H

#include "bitmap.h"
#include <stdio.h>

#define EH_FOLHA 1

typedef struct Arvore Arvore;

Arvore *TreeConstruct(int codigo, int num_eventos, int ehfolha);

Arvore *TreePushBack(Arvore *raiz1, Arvore *raiz2);

void TreePrint(Arvore *arv);

void BinaryTreePrint(Arvore *arv);

Arvore *BinaryTreeDestroy(Arvore *arv);

int TreesCompare(const void *t1, const void *t2);

int TreeHeight(Arvore *raiz);

void GetTreeBitsSize(Arvore *raiz, int id_profundidade, unsigned int *size);

void CompactaHuffmanTree(Arvore *raiz, char *codigo, int id_profundidade, bitmap *tree_bitmap);

Arvore *GetLeftTree(Arvore *arv);

Arvore *GetRightTree(Arvore *arv);

char GetTreeChar(Arvore *arv);

int EhFolha(Arvore *arv);

Arvore *DescompactaHuffmanTree(char *array_bits, int *index, int tam_max);

char Le_Bit(char *array_bits, int *index);

char Le_Caracter(char *array_bits, int *index);

unsigned int Le_QtdBits(FILE *input_file);

void OriginalFileReconstruct(Arvore *raiz, int *flag, FILE *output_file);

#endif