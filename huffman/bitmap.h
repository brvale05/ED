/** Define um TAD representando um mapa de bits.
 * @file bitmap.h
 * @author Joao Paulo Andrade Almeida (jpalmeida@inf.ufes.br)
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <stdio.h>

/**
 * Estrutura para representar um mapa de bits.
 */
typedef struct map bitmap;

unsigned char* bitmapGetContents(bitmap* bm);

unsigned int bitmapGetMaxSize(bitmap* bm);

unsigned int bitmapGetLength(bitmap* bm);

bitmap* bitmapInit(unsigned int max_size);

unsigned char bitmapGetBit(bitmap* bm, unsigned int index);

void bitmapAppendLeastSignificantBit(bitmap* bm, unsigned char bit);

void bitmapLibera (bitmap* bm);

bitmap *BitMapDescompacta(unsigned int max_size, FILE *input_file);

void *PreencheBitsArray(char *array_bits, int tam, bitmap *tree_bm);

unsigned int Le_QtdBits(FILE *input_file);

char Le_Bit(char *array_bits, int *index);

char Le_Caracter(char *array_bits, int *index);

#endif /*BITMAP_H_*/
