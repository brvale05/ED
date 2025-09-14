/**
 * @file listaArvores.h
 * @brief Arquivo de cabeçalho para a estrutura de dados de Lista Encadeada de Árvores.
 * @author Bruno Vale e Davi sena
 * Este arquivo define a interface para uma lista encadeada especializada
 * em armazenar e manipular ponteiros para Árvores (Arv*). A lista é
 * mantida ordenada pela frequência dos caracteres nas árvores, sendo
 * fundamental para a implementação do algoritmo de Huffman.
 */

#ifndef LISTA
#define LISTA

// Inclui o cabeçalho da estrutura de Árvore, pois a lista irá armazenar elementos desse tipo.
#include "arvore.h"

/**
 * @brief Declaração avançada (forward declaration) da estrutura Lista.
 * Permite que outros arquivos usem ponteiros para 'Lista' (Lista*) sem
 * precisar conhecer os detalhes de sua implementação, que está no arquivo .c.
 */
typedef struct Lista Lista;

/**
 * @brief Verifica se a lista está vazia.
 * @param l Ponteiro para a lista.
 * @return Retorna um valor verdadeiro (diferente de 0) se a lista estiver vazia e falso (0) caso contrário.
 */
int lista_vazia(Lista *l);

/**
 * @brief Aloca e inicializa uma nova lista vazia.
 * @return Ponteiro para a lista recém-criada.
 */
Lista *criaLista();

/**
 * @brief Insere uma árvore na lista de forma ordenada.
 * A inserção mantém a lista ordenada em ordem crescente de acordo com a frequência da árvore.
 * @param a Ponteiro para a árvore a ser inserida.
 * @param Lista Ponteiro para a lista onde a árvore será inserida.
 * @return O tipo de retorno 'void*' é incomum; geralmente seria 'void'. A função não retorna um valor útil.
 */
void *insereNaLista(Arv *a, Lista *Lista);

/**
 * @brief Realiza a junção das árvores na lista até restar apenas uma.
 * Este é o passo principal do algoritmo de Huffman: remove as duas árvores de menor frequência,
 * junta-as em uma nova árvore e a insere de volta na lista, repetindo o processo
 * até que a lista contenha apenas a árvore de Huffman completa.
 * @param l Ponteiro para a lista de árvores.
 * @param eh_unicaArvore Flag que determina se existe apenas um nó.
 */
void juncao_arvs_lista(Lista *l, int eh_unicaArvore);

/**
 * @brief Retira as duas primeiras árvores da lista.
 * Função auxiliar para 'juncao_arvs_lista', remove os dois nós de menor frequência
 * (os dois primeiros elementos) da lista.
 * @param l Ponteiro para a lista.
 */
void retira_duasArv_Da_Lista(Lista *l);

/**
 * @brief Libera toda a memória alocada para a lista.
 * Percorre todos os elementos da lista, liberando a memória de cada árvore contida nela
 * e dos nós da própria lista.
 * @param l Ponteiro para a lista a ser desalocada.
 */
void desalocaLista(Lista *l);

/**
 * @brief Retorna a primeira árvore da lista.
 * Usada após a 'juncao_arvs_lista' para obter a árvore de Huffman final,
 * que é o único elemento restante na lista.
 * @param l Ponteiro para a lista.
 * @return Ponteiro para a primeira árvore na lista.
 */
Arv *retorna_Prim_arv(Lista *l);

/**
 * @brief Verifica se a lista contém apenas um elemento.
 * Útil para determinar o critério de parada do algoritmo de Huffman, quando a lista é reduzida à árvore final.
 * @param l Ponteiro para a lista.
 * @return Retorna 1 se a lista tiver um único elemento, e 0 caso contrário.
 */
int unico_elem_lista(Lista *l);

#endif