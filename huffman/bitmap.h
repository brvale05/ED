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

/**
 * Funcao auxiliar que imprime uma mensagem de falha e aborta o programa caso testresult seja falso.
 * @param testresult Valor booleano representando o resultado do teste que deveria ser verdadeiro.
 * @param message A mensagem para ser impressa se resultado do teste for falso.
 */
void assert(int testresult, char *message);

/**
 * Retorna o conteudo do mapa de bits.
 * @param bm O mapa de bits.
 */
unsigned char *bitmapGetContents(bitmap *bm);

/**
 * Retorna o tamanho maximo do mapa de bits.
 * @param bm O mapa de bits.
 * @return O tamanho maximo do mapa de bits.
 */
unsigned int bitmapGetMaxSize(bitmap *bm);

/**
 * Retorna o tamanho atual do mapa de bits.
 * @param bm O mapa de bits.
 * @return O tamanho atual do mapa de bits.
 */
unsigned int bitmapGetLength(bitmap *bm);

/**
 * Constroi um novo mapa de bits, definindo um tamanho maximo.
 * @param max_size O tamanho maximo para o mapa de bits.
 * @return O mapa de bits inicializado.
 */
bitmap *bitmapInit(unsigned int max_size);

/**
 * Retorna o valor do bit na posicao index.
 * @param bm O mapa de bits.
 * @param index A posicao do bit.
 * @pre index<bitmapGetLength(bm)
 * @return O valor do bit.
 */
unsigned char bitmapGetBit(bitmap *bm, unsigned int index);

/**
 * Modifica o valor do bit na posicao index.
 * @param bm O mapa de bits.
 * @param index A posicao do bit.
 * @param bit O novo valor do bit.
 * @post bitmapGetBit(bm,index)==bit
 */
static void bitmapSetBit(bitmap *bm, unsigned int index, unsigned char bit);

/**
 * Adiciona um bit no final do mapa de bits.
 * @param bm O mapa de bits.
 * @param bit O novo valor do bit.
 * @pre bitmapGetLength(bm) < bitmapGetMaxSize(bm)
 * @post (bitmapGetBit(bm,bitmapGetLength(bm) @ pre)==bit)
 * and (bitmapGetLength(bm) == bitmapGetLength(bm) @ pre+1)
 */
void bitmapAppendLeastSignificantBit(bitmap *bm, unsigned char bit);

/**
 * Libera a memória dinâmica alocada para o mapa de bits.
 * @param bm O mapa de bits.
 */
void bitmapLibera(bitmap *bm);

/**
 * Constrói e retorna um novo mapa de bits, descompactando-o a partir de um arquivo.
 * A função lê a estrutura do mapa de bits do arquivo de entrada e a reconstrói na memória.
 * @param max_size O tamanho máximo do mapa de bits a ser reconstruído.
 * @param input_file O arquivo de onde o mapa de bits será lido.
 * @return O mapa de bits descompactado e reconstruído.
 */
bitmap *BitMapDescompacta(unsigned int max_size, FILE *input_file);

/**
 * Preenche um array de caracteres com os bits de um mapa de bits.
 * Isso pode ser usado para transferir os dados da estrutura `bitmap` para um array
 * mais conveniente para manipulação.
 * @param array_bits O array de caracteres que será preenchido.
 * @param tam O tamanho do array de bits.
 * @param tree_bm O mapa de bits de uma árvore de onde os dados serão lidos.
 */
void *PreencheBitsArray(char *array_bits, int tam, bitmap *tree_bm);

/**
 * Lê a quantidade de bits de um arquivo de entrada.
 * Geralmente, essa informação é usada para determinar o tamanho do conteúdo comprimido.
 * @param input_file O arquivo de onde a quantidade de bits será lida.
 * @return A quantidade de bits lida.
 */
unsigned int Le_QtdBits(FILE *input_file);

/**
 * Lê um único bit de um array de caracteres que contém dados binários.
 * O índice é atualizado após a leitura para apontar para o próximo bit.
 * @param array_bits O array de caracteres com os dados binários.
 * @param index O ponteiro para o índice que controla a posição de leitura no array.
 * @return O bit lido (0 ou 1).
 */
char Le_Bit(char *array_bits, int *index);

/**
 * Lê um caractere completo (8 bits) de um array de caracteres.
 * O índice é atualizado para a próxima posição após a leitura.
 * @param array_bits O array de caracteres com os dados binários.
 * @param index O ponteiro para o índice que controla a posição de leitura no array.
 * @return O caractere lido.
 */
char Le_Caracter(char *array_bits, int *index);

#endif /*BITMAP_H_*/
