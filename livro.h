/*
 * =======================================================
 *  Arquivo: livro.h
 *  Autor: Bruno Vale Lourenço
 * =======================================================
 */
#ifndef LIVRO_H
#define LIVRO_H

#include <stdio.h>

// Declaração opaca da estrutura Livro, promovendo encapsulamento.
// Os detalhes da estrutura são definidos em outro lugar (provavelmente no .c).
typedef struct Livro Livro;

/**
 * Constrói um novo livro com os dados fornecidos.
 * @param id Identificador do livro.
 * @param titulo Título do livro.
 * @param autor Nome do autor.
 * @param genero Gênero do livro.
 * @param ano Ano de publicação.
 * @return Ponteiro para a estrutura Livro criada.
 */
Livro *BookConstruct(int id, char *titulo, char *autor, char *genero, int ano);

/**
 * Lê um livro de um arquivo.
 * @param b_file Ponteiro para o arquivo.
 * @param flag Parâmetro que pode controlar o tipo de leitura.
 * @return Ponteiro para a estrutura Livro lida.
 */
Livro *Le_Book(FILE *b_file, int flag);

/**
 * Libera a memória associada a um livro.
 * @param dado Ponteiro para o livro a ser destruído.
 */
void BookDestroy(void *dado);

/**
 * Imprime os dados de um livro no arquivo fornecido.
 * @param data Ponteiro para o livro.
 * @param stdout_f Ponteiro para o arquivo onde será feita a impressão.
 */
void PrintBook(void *data, FILE *stdout_f);

/**
 * Compara o ID de um livro com um ID fornecido.
 * @param data Ponteiro para o livro.
 * @param id Ponteiro para o ID a ser comparado.
 * @return Resultado da comparação (tipicamente 1 se igual, 0 se diferente).
 */
int BookCompare(void *data, void *id);

/**
 * Retorna o título de um livro.
 * @param b Ponteiro para o livro.
 * @return Ponteiro para a string com o título.
 */
char *GetBookTitle(Livro *b);

/**
 * Retorna o ID de um livro.
 * @param b Ponteiro para o livro.
 * @return ID do livro.
 */
int GetBookId(Livro *b);

#endif