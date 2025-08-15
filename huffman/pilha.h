#ifndef PILHA_H
#define PILHA_H
#define TAM_MAX_PILHA 10000

#include "arvore.h"

/**
 * Estrutura para representar a Pilha.
 */
typedef struct Pilha Pilha;

/**
 * Constrói e inicializa uma nova Pilha.
 * @return Um ponteiro para a Pilha recém-criada.
 */
Pilha *PilhaConstruct();

/**
 * Libera a memória alocada para a Pilha.
 * @param p O ponteiro para a Pilha a ser destruída.
 */
void PilhaDestroy(Pilha *p);

/**
 * Ordena os elementos da Pilha.
 * A ordenação é baseada na frequência dos caracteres, para ser usada na construção da Árvore de Huffman.
 * @param p O ponteiro para a Pilha.
 */
void OrdenaPilha(Pilha *p);

/**
 * Cria e adiciona uma árvore ao final da Pilha com as informações necessárias.
 * @param p O ponteiro para a Pilha.
 * @param array O array de inteiros (frequências) a ser adicionado na árvore.
 */
void PilhaPushBack(Pilha *p, unsigned int *array);

/**
 * Constrói a Árvore de Huffman a partir dos nós contidos na Pilha.
 * O processo de construção da árvore consome os nós da pilha (chama o qsort a cada iteração).
 * @param p O ponteiro para a Pilha com os nós.
 * @return Um ponteiro para o nó raiz da Árvore de Huffman construída.
 */
Arvore *HuffmanTreeConstruct(Pilha *p);

/**
 * Verifica se a Pilha está cheia.
 * @param p O ponteiro para a Pilha.
 * @return 1 se a Pilha estiver cheia, 0 caso contrário.
 */
int Cheia(Pilha *p);

#endif