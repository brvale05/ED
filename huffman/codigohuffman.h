#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

#include "bitmap.h"

/**
 * @brief Estrutura que representa o código de Huffman para um caractere.
 * Armazena o caractere original, sua sequência de bits e o tamanho da sequência.
 */
typedef struct CodigoHuffman CodigoHuffman;

/**
 * @brief Constrói e inicializa uma nova estrutura CodigoHuffman.
 * @param code A sequência de bits (como string de '0's e '1's) que representa o código.
 * @param tam O tamanho da sequência de bits.
 * @param car O caractere original que o código representa.
 * @return Um ponteiro para a estrutura CodigoHuffman recém-criada.
 */
CodigoHuffman *CodigoHuffmanConstruct(char *code, int tam, unsigned char car);

/**
 * @brief Libera a memória alocada para a estrutura CodigoHuffman.
 * @param h O ponteiro para a estrutura CodigoHuffman a ser destruída.
 */
void CodigoHuffmanDestroy(CodigoHuffman *h);

/**
 * @brief Escreve os dados compactados em um arquivo binário.
 * A função recebe os mapas de bits do conteúdo e da árvore de Huffman, junto com a quantidade de bits, e os salva em um arquivo.
 * @param map O mapa de bits que contém a sequência de bits do arquivo original.
 * @param tree_map O mapa de bits que representa a Árvore de Huffman.
 * @param qtdbits_map O número total de bits no mapa de bits do conteúdo.
 * @param qtdbits_treemap O número total de bits no mapa de bits da árvore.
 * @param caminho O caminho do arquivo onde os dados compactados serão salvos.
 */
void WriteFileCompactado(bitmap *map, bitmap *tree_map, unsigned int qtdbits_map, unsigned int qtdbits_treemap, char *caminho);

/**
 * @brief Retorna o tamanho da sequência de bits do código de Huffman.
 * @param h O ponteiro para a estrutura CodigoHuffman.
 * @return O tamanho da sequência de bits.
 */
int GetTamHuffmanCode(CodigoHuffman *h);

/**
 * @brief Retorna o bit na posição especificada do código de Huffman.
 * @param h O ponteiro para a estrutura CodigoHuffman.
 * @param id O índice do bit a ser retornado.
 * @return O bit na posição 'id' ('0' ou '1').
 */
char GetBitHuffmanCode(CodigoHuffman *h, int id);

#endif