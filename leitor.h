/*
 * =======================================================
 *  Arquivo: leitor.h
 *  Autor: Bruno Vale Lourenço
 * =======================================================
 */
#ifndef LEITOR_H
#define LEITOR_H

#include "lista.h"
#include "livro.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Tipo opaco que representa um leitor
typedef struct Leitor Leitor;

/**
 * Constrói e inicializa um novo leitor.
 * 
 * @param id ID único do leitor.
 * @param nome Nome do leitor.
 * @param p_list Lista de preferências do leitor.
 * @return Ponteiro para a estrutura Leitor criada.
 */
Leitor *ReaderConstruct(int id, char *nome, Lista *p_list);

/**
 * Libera a memória alocada para um leitor.
 * 
 * @param data Ponteiro genérico para o leitor a ser destruído.
 */
void ReaderDestroy(void *data);

/**
 * Lê um leitor a partir de um arquivo.
 * 
 * @param r_file Arquivo de onde os dados do leitor serão lidos.
 * @param flag Flag de controle (pode definir o modo de leitura).
 * @return Ponteiro para a estrutura Leitor lida.
 */
Leitor *Le_Reader(FILE *r_file, int flag);

/**
 * Compara o ID de um leitor com um ID fornecido.
 * 
 * @param data Ponteiro genérico para um leitor.
 * @param id Ponteiro para um inteiro representando o ID a ser comparado.
 * @return 1 se os IDs forem iguais, valor igual a 0 caso contrário.
 */
int ReaderCompare(void *data, void *id);

/**
 * Imprime os dados de um leitor em um arquivo de saída.
 * 
 * @param data Ponteiro genérico para o leitor.
 * @param stdout_f Arquivo onde a saída será impressa.
 */
void PrintReader(void *data, FILE *stdout_f);

/**
 * Retorna a lista de preferências do leitor.
 * 
 * @param reader Ponteiro para o leitor.
 * @return Ponteiro para a lista de preferências (Lista*).
 */
Lista *GetPrefList(Leitor *reader);

/**
 * Retorna a lista de livros lidos pelo leitor.
 * 
 * @param reader Ponteiro para o leitor.
 * @return Ponteiro para a lista de livros lidos (Lista*).
 */
Lista *GetLidosList(Leitor *reader);

/**
 * Retorna a lista de desejos do leitor.
 * 
 * @param reader Ponteiro para o leitor.
 * @return Ponteiro para a lista de desejos (Lista*).
 */
Lista *GetWishList(Leitor *reader);

/**
 * Retorna a lista de recomendações (RecList) do leitor.
 * 
 * A RecList é a lista de livros recomendados por outros leitores.
 * 
 * @param reader Ponteiro para o leitor.
 * @return Ponteiro para a lista de recomendações (Lista*).
 */
Lista *GetRecList(Leitor *reader);

/**
 * Retorna o nome do leitor.
 * 
 * @param reader Ponteiro para o leitor.
 * @return String com o nome do leitor.
 */
char *GetReaderName(Leitor *reader);

/**
 * Retorna o ID do leitor.
 * 
 * @param reader Ponteiro para o leitor.
 * @return Inteiro representando o ID do leitor.
 */
int GetReaderId(Leitor *reader);

/**
 * Função auxiliar que atualiza a afinidade entre dois leitores com base em suas preferências.
 * 
 * @param reader1 Ponteiro para o primeiro leitor.
 * @param reader2 Ponteiro para o segundo leitor.
 */
void UpdateAfinidades_Aux(Leitor *reader1, Leitor *reader2);

/**
 * Imprime os livros em comum de uma lista.
 * 
 * @param books_list Lista de livros em comum.
 * @param stdout_file Arquivo onde os dados serão impressos.
 */
void Imprime_Livros_Em_Comum(Lista *books_list, FILE *stdout_file);

/**
 * Descobre e imprime os livros em comum entre dois leitores.
 * 
 * @param reader1 Ponteiro para o primeiro leitor.
 * @param reader2 Ponteiro para o segundo leitor.
 * @param stdout_file Arquivo onde a saída será impressa.
 */
void Descobre_Livros_Em_Comum(Leitor *reader1, Leitor *reader2, FILE *stdout_file);

/**
 * Realiza uma busca em profundidade de afinidades entre leitores para encontrar conexão entre dois leitores.
 * 
 * @param leitor_origem Leitor de origem.
 * @param leitor_alvo Leitor de destino.
 * @param stdout_file Arquivo de saída dos resultados.
 */
void GrafoSearchAfinidades(Leitor *leitor_origem, Leitor *leitor_alvo, FILE *stdout_file);

/**
 * Função recursiva auxiliar para busca no grafo entre leitores.
 * 
 * @param leitor_origem Leitor atual na busca.
 * @param leitor_alvo Leitor que se deseja alcançar.
 * @param visitados Lista de leitores já visitados (para evitar ciclos).
 * @return 1 se encontrou caminho, 0 caso contrário.
 */
int GrafoSearch(Leitor *leitor_origem, Leitor *leitor_alvo, Lista *visitados);

/**
 * Adiciona um livro à lista de lidos do leitor.
 * 
 * @param reader Ponteiro para o leitor.
 * @param book Livro a ser adicionado.
 * @param stdout_file Arquivo de saída para mensagens de confirmação.
 */
void AddLidosList(Leitor *reader, Livro *book, FILE *stdout_file);

/**
 * Adiciona um livro à lista de desejos do leitor.
 * 
 * @param reader Ponteiro para o leitor.
 * @param book Livro a ser adicionado.
 * @param stdout_file Arquivo de saída para mensagens de confirmação.
 */
void AddWishList(Leitor *reader, Livro *book, FILE *stdout_file);

/**
 * Adiciona um livro à lista de recomendações (RecList) de um leitor.
 * 
 * @param reader_inicial Leitor que faz a recomendação.
 * @param reader_destino Leitor que receberá a recomendação.
 * @param book Livro sendo recomendado.
 * @param stdout_file Arquivo de saída para mensagens de confirmação.
 */
void AddRecList(Leitor *reader_inicial, Leitor *reader_destino, Livro *book, FILE *stdout_file);

/**
 * Aceita uma recomendação da RecList, movendo o livro para a lista de lidos do leitor destino.
 * 
 * @param reader_origem Leitor que fez a recomendação.
 * @param reader_destino Leitor que está aceitando a recomendação.
 * @param id ID do livro recomendado.
 * @param stdout_file Arquivo de saída para mensagens.
 */
void AceitaRecomendacao(Leitor *reader_origem, Leitor *reader_destino, int id, FILE *stdout_file);

/**
 * Recusa uma recomendação da RecList, removendo-a da lista do leitor destino.
 * 
 * @param reader_origem Leitor que fez a recomendação.
 * @param reader_destino Leitor que está recusando a recomendação.
 * @param id ID do livro recomendado.
 * @param stdout_file Arquivo de saída para mensagens.
 */
void RecusaRecomendacao(Leitor *reader_origem, Leitor *reader_destino, int id, FILE *stdout_file);

#endif
