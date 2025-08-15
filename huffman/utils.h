#ifndef UTILS_H
#define UTILS_H

#define DESCOMPACTA 1 // Flag indicando operação de descompactação

#include <stdio.h>

/**
 * Abre um arquivo no modo especificado.
 * @param caminho   Caminho do arquivo.
 * @param mode      Modo de abertura ("rb", "wb", etc.).
 * @param flag_tipo Tipo de operação (ex: DESCOMPACTA para descompactação).
 * @return Ponteiro para o arquivo aberto.
 */
FILE *OpenFile(char *caminho, char *mode, int flag_tipo);

/**
 * Fecha um arquivo.
 * @param f Ponteiro para o arquivo a ser fechado.
 */
void CloseFile(FILE *f);

/**
 * Conta a frequência de cada caractere presente em um arquivo.
 * @param array   Vetor de frequências (256 posições).
 * @param caminho Caminho do arquivo a ser lido.
 */
void FrequencyCount(unsigned int *array, char *caminho);

#endif
