/**
 * @file arvore.h
 * @brief Arquivo de cabeçalho para a estrutura de dados de Árvore Binária.
 * @author Bruno Vale e Davi sena
 *
 * Este arquivo define a interface para uma árvore binária usada para construir
 * a árvore de Huffman. Cada nó da árvore pode representar uma folha (contendo
 * um caractere e sua frequência) ou um nó interno (agrupando sub-árvores).
 */

#ifndef ARVORE 
#define ARVORE 

#define EH_FOLHA 1

/**
 * @brief Declaração avançada (forward declaration) da estrutura Arv.
 * Permite o uso de ponteiros para 'Arv' (Arv*) em outras partes do programa
 * sem a necessidade da definição completa da struct, que está no arquivo .c.
 */
typedef struct Arv Arv;

/**
 * @brief Cria uma árvore vazia.
 * Na prática, inicializa um ponteiro de árvore com o valor NULL.
 * @return Retorna NULL, representando uma árvore vazia.
 */
Arv *criaArv_vazia();

/**
 * @brief Verifica se uma árvore (ou sub-árvore) está vazia.
 * @param a Ponteiro para a árvore.
 * @return Retorna um valor verdadeiro (diferente de 0) se a árvore for NULL, e falso (0) caso contrário.
 */
int arv_vazia(Arv *a);

/**
 * @brief Cria e insere um nó folha na árvore.
 * Esta função é usada para criar as árvores iniciais, onde cada uma representa um caractere e sua frequência.
 * @param a Ponteiro para a árvore (geralmente vazia/NULL ao chamar).
 * @param valorAscii O código ASCII do caractere a ser armazenado no nó.
 * @param freq A frequência de ocorrência do caractere.
 * @param eh_folha Flag que determina se o nó é folha ou não (1 para folha, 0 para o contrário).
 * @return Ponteiro para a nova árvore/nó criado.
 */
Arv *insere_Arv(Arv *a, int valorAscii, int freq, int eh_folha);

/**
 * @brief Junta duas árvores em uma nova árvore.
 * Cria um novo nó interno que tem as duas árvores passadas como parâmetro como filhos (esquerda e direita).
 * A frequência do novo nó é a soma das frequências dos filhos.
 * @param a1 A primeira árvore (será o filho da esquerda).
 * @param a2 A segunda árvore (será o filho da direita).
 * @return Ponteiro para a nova árvore resultante da junção.
 */
Arv *junta_arvs(Arv *a1, Arv *a2);

/**
 * @brief Calcula a altura de uma árvore.
 * @param a Ponteiro para a raiz da árvore.
 * @return A altura da árvore. Uma árvore vazia tem altura -1.
 */
int altura_arv(Arv *a);

/**
 * @brief Retorna a frequência armazenada em um nó da árvore.
 * @param a Ponteiro para o nó da árvore.
 * @return O valor da frequência.
 */
int frequencia_arv(Arv *a);

/**
 * @brief Verifica se um nó da árvore é uma folha.
 * @param a Ponteiro para o nó da árvore.
 * @return Retorna verdadeiro (1) se for uma folha, e falso (0) caso contrário.
 */
int folha_arv(Arv *a);

/**
 * @brief Retorna o caractere armazenado em um nó folha.
 * @param a Ponteiro para o nó da árvore.
 * @return O caractere.
 */
unsigned char char_arv(Arv *a);

/**
 * @brief Retorna a sub-árvore à esquerda de um nó.
 * @param a Ponteiro para o nó pai.
 * @return Ponteiro para o filho da esquerda.
 */
Arv *esqueda_arv(Arv *a);

/**
 * @brief Retorna a sub-árvore à direita de um nó.
 * @param a Ponteiro para o nó pai.
 * @return Ponteiro para o filho da direita.
 */
Arv *direita_arv(Arv *a);

/**
 * @brief Libera toda a memória alocada para uma árvore.
 * Percorre a árvore recursivamente e libera a memória de todos os seus nós.
 * @param a Ponteiro para a raiz da árvore a ser liberada.
 */
void libera_arv(Arv *a);

/**
 * @brief Calcula a quantidade de bits necessários para representar a estrutura da árvore.
 * A função percorre a árvore para determinar o tamanho total do cabeçalho binário.
 * @param raiz Ponteiro para a raiz da árvore de Huffman.
 * @param bits Ponteiro para uma variável que acumulará o número total de bits.
 */
void bits_arv(Arv *raiz, unsigned int *bits);

/**
 * @brief Reconstrói a árvore de Huffman a partir de uma sequência de bits.
 * Essencial para o processo de descompressão, ela lê a sequência de bits para recriar a estrutura da árvore e os caracteres.
 * @param array_bits Sequência de bits que contém a representação da árvore.
 * @param index Ponteiro para um índice que controla a posição atual na sequência de bits.
 * @param tam_max Tamanho total da sequência de bits.
 * @return Ponteiro para a raiz da árvore reconstruída.
 */
Arv *huffmanTree_descompacta(char *array_bits, int *index, int tam_max);

/**
 * @brief Verifica se a árvore é composta por um único nó folha.
 * Esta é uma condição de caso especial no algoritmo de Huffman, para arquivos que contêm apenas um tipo de caractere.
 * @param tree Ponteiro para a raiz da árvore.
 * @return Retorna 1 se a árvore tiver um único nó, e 0 caso contrário.
 */
int eh_unica_arv(Arv *tree);


#endif