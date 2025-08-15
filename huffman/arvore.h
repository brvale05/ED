#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include "bitmap.h"

#define EH_FOLHA 1 // Valor usado para indicar que um nó da árvore é folha

// Definição opaca da estrutura da árvore (implementação no .c)
typedef struct Arvore Arvore;

/**
 * Cria um nó de árvore de Huffman.
 * @param codigo        Código ASCII associado ao nó.
 * @param num_eventos   Frequência do símbolo.
 * @param ehfolha       Define se o nó é folha (EH_FOLHA) ou não.
 * @return Ponteiro para a árvore criada.
 */
Arvore *TreeConstruct(int codigo, int num_eventos, int ehfolha);

/**
 * Cria uma nova raiz juntando duas subárvores.
 * @param raiz1 Ponteiro para a subárvore esquerda.
 * @param raiz2 Ponteiro para a subárvore direita.
 * @return Ponteiro para a nova árvore.
 */
Arvore *TreePushBack(Arvore *raiz1, Arvore *raiz2);

/**
 * Libera toda a memória usada pela árvore.
 * @param arv Ponteiro para a árvore.
 * @return Retorna NULL.
 */
Arvore *BinaryTreeDestroy(Arvore *arv);

/**
 * Função de comparação de árvores (usada em ordenação por frequência).
 * @param t1 Ponteiro para árvore 1.
 * @param t2 Ponteiro para árvore 2.
 * @return Valor negativo, zero ou positivo (igual qsort).
 */
int TreesCompare(const void *t1, const void *t2);

/**
 * Calcula a altura da árvore.
 * @param raiz Ponteiro para a árvore.
 * @return Altura da árvore (em níveis).
 */
int TreeHeight(Arvore *raiz);

/**
 * Calcula o tamanho total, em bits, da representação da árvore.
 * @param raiz           Ponteiro para a árvore.
 * @param id_profundidade Profundidade atual (usada na recursão).
 * @param size           Ponteiro para variável que acumula o tamanho total.
 */
void GetTreeBitsSize(Arvore *raiz, int id_profundidade, unsigned int *size);

/**
 * Compacta a árvore de Huffman em um bitmap para armazenamento.
 * @param raiz           Ponteiro para a árvore.
 * @param codigo         String temporária que armazena o caminho de bits até o nó folha.
 * @param id_profundidade Profundidade atual.
 * @param tree_bitmap    Ponteiro para o bitmap onde será armazenada a árvore.
 */
void CompactaHuffmanTree(Arvore *raiz, char *codigo, int id_profundidade, bitmap *tree_bitmap);

/**
 * Retorna a subárvore à esquerda.
 * @param arv Ponteiro para a árvore.
 */
Arvore *GetLeftTree(Arvore *arv);

/**
 * Retorna a subárvore à direita.
 * @param arv Ponteiro para a árvore.
 */
Arvore *GetRightTree(Arvore *arv);

/**
 * Retorna o caractere armazenado no nó.
 * @param arv Ponteiro para a árvore.
 * @return Valor do caractere (unsigned char).
 */
unsigned char GetTreeChar(Arvore *arv);

/**
 * Verifica se um nó é folha.
 * @param arv Ponteiro para a árvore.
 * @return 1 se for folha, 0 caso contrário.
 */
int EhFolha(Arvore *arv);

/**
 * Reconstrói a árvore de Huffman a partir de um vetor de bits.
 * @param array_bits Vetor de bits.
 * @param index      Ponteiro para índice atual na leitura.
 * @param tam_max    Tamanho máximo do vetor de bits.
 * @return Ponteiro para a árvore reconstruída.
 */
Arvore *DescompactaHuffmanTree(char *array_bits, int *index, int tam_max);

#endif
