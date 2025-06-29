#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>

typedef struct Lista Lista;

typedef struct Celula Celula;

struct Celula
{
    Celula *prox;
    void *data;
};

typedef void (*fptr_print)(void *data, FILE *stdout_f);

typedef void (*fptr_destroy)(void *data);

typedef int (*fptr_compare)(void *dado, void *id);

/**
 * @brief Função que retorna uma estrutura do tipo Lista alocada dinamicamente.
 */
Lista *ListConstruct();

/**
 * @brief Função que executa os comandos da booked.
 * 
 * @param list Ponteiro para uma Lista.
 * @param data Ponteiro para um tipo void a ser adicionado na Lista.
 */
void ListPushBack(Lista *list, void *data);

/**
 * @brief Função que desaloca uma estrutura do tipo Lista.
 * 
 * @param list Ponteiro para uma Lista.
 * @param libera_flag Flag que determina se a função deve liberar ou não o tipo void guardado na Lista.
 * @param destroy Ponteiro de função que desaloca algum tipo dado.
 */
void ListDestroy(Lista *list, int libera_flag, fptr_destroy destroy);

/**
 * @brief Função que busca um dado em uma Lista.
 * 
  * @param list Ponteiro para uma Lista.
 * @param id Ponteiro para o ID do dado.
 * @param compara Ponteiro de função que compara um item com o ID informado.
 */
void* ListSearch(Lista *list, void *id, fptr_compare compara);

/**
 * @brief Função que remove um dado de uma Lista.
 * 
  * @param list Ponteiro para uma Lista.
 * @param compara Ponteiro de função que compara um item com o ID informado.
 * @param id Ponteiro para o ID do dado.
 */
void *ListRemove(Lista *list, fptr_compare compara, void *id);

/**
 * @brief Função que imprime uma Lista no arquivo de saída.
 * 
 * @param list Ponteiro para uma Lista.
 * @param imprime Ponteiro de função que imprime um dado específico.
 * @param stdout_f Arquivo de saída.
 * @param flag_comma Flag que determina se devo ou não imprimir uma vírgula.
 */
void ListPrint(Lista *list, fptr_print imprime, FILE *stdout_f, int flag_comma);

/**
 * @brief Função que retorna o dado contido na célula de uma Lista.
 * 
 * @param c Ponteiro para célula.
 */
void *GetDataCell(Celula *c);

/**
 * @brief Função que retorna a primeira célula de uma Lista.
 * 
 * @param l Ponteiro para uma Lista.
 */
Celula *GetFirstCell(Lista *l);

#endif