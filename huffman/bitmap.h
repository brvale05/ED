/** Define um TAD representando um mapa de bits.
 * @file bitmap.h
 * @author Joao Paulo Andrade Almeida (jpalmeida@inf.ufes.br)
 */

#ifndef BITMAP_H_
#define BITMAP_H_

#include <stdio.h>

#include "codificacao.h"
#include "arvore.h"

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
 * @brief Libera a memória alocada para o bitmap.
 * @param bm Ponteiro para o bitmap a ser desalocado.
 */
void bitmapLibera(bitmap *bm);

/**
 * @brief Preenche o bitmap com os códigos de Huffman de um caractere.
 * Esta função consulta a tabela de codificação para obter o código do caractere e o adiciona ao bitmap.
 * @param bm Ponteiro para o bitmap a ser preenchido.
 * @param tabela Tabela de codificação de Huffman.
 * @param car O caractere cujo código será adicionado.
 */
void bitmap_preenche(bitmap *bm, Cod **tabela, unsigned char car);

/**
 * @brief Adiciona a estrutura da árvore de Huffman ao bitmap.
 * Esta função percorre a árvore e codifica sua estrutura (nós internos e folhas) para que possa ser salva no cabeçalho do arquivo compactado.
 * @param a Ponteiro para a raiz da árvore de Huffman.
 * @param bm Ponteiro para o bitmap onde a estrutura da árvore será armazenada.
 */
void coloca_arvore_bitmap(Arv *a, bitmap *bm);

/**
 * @brief Escreve os dados compactados e a árvore de Huffman em um arquivo.
 * Esta é a função final de compactação, que organiza e salva o cabeçalho (com a árvore) e o conteúdo compactado no arquivo de saída.
 * @param bm Bitmap com o conteúdo do arquivo compactado.
 * @param qntdbits Quantidade de bits do conteúdo compactado.
 * @param arv_bm Bitmap com a representação da árvore.
 * @param arv_bits Quantidade de bits da árvore.
 * @param caminho Caminho para o arquivo de saída.
 */
void escreve_arquivo_Compactado(bitmap *bm, unsigned int qntdbits, bitmap *arv_bm, unsigned int arv_bits, char *caminho);

/**
 * @brief Lê a quantidade de bits do cabeçalho do arquivo compactado.
 * Função usada na descompressão para determinar o número de bits válidos a serem lidos do arquivo.
 * @param input_file O arquivo compactado.
 * @return A quantidade de bits lida.
 */
unsigned int le_qtdbits(FILE *input_file);

/**
 * @brief Lê os dados compactados de um arquivo e os armazena em um bitmap.
 * @param max_size O tamanho máximo de bits a serem lidos.
 * @param input_file O arquivo de entrada compactado.
 * @return Ponteiro para o bitmap preenchido.
 */
bitmap *bitmap_descompacta(unsigned int max_size, FILE *input_file);

/**
 * @brief Copia os bits de um bitmap para um array de caracteres.
 * Usada para extrair a representação da árvore de Huffman do bitmap e passá-la para a função de reconstrução da árvore.
 * @param array_bits O array de destino.
 * @param tam O tamanho do array.
 * @param tree_bm O bitmap que contém a representação da árvore.
 */
void preenche_bits_array(char *array_bits, int tam, bitmap *tree_bm);

/**
 * @brief Função auxiliar para reconstruir o arquivo original.
 * Percorre a árvore de Huffman usando os bits do bitmap compactado, escrevendo os caracteres no arquivo de saída.
 * @param raiz Ponteiro para a raiz da árvore de Huffman.
 * @param flag Ponteiro para uma flag que indica o final da descompactação.
 * @param output_file O arquivo de saída.
 */
void file_reconstruct_aux(Arv *raiz, int *flag, FILE *output_file);

/**
 * @brief Descompacta e reconstrói o arquivo original.
 * Orquestra o processo de descompressão, usando a árvore e o bitmap de bits para decodificar e escrever o conteúdo no arquivo de saída.
 * @param raiz Ponteiro para a raiz da árvore de Huffman.
 * @param bm Bitmap com o conteúdo compactado.
 * @param caminho Caminho para o arquivo de saída.
 * @param arq_vazio Flag que indica se o arquivo original estava vazio.
 */
void file_reconstruct(Arv *raiz, bitmap *bm, char *caminho, int arq_vazio);

#endif /*BITMAP_H_*/
