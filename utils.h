/*
 * =======================================================
 *  Arquivo: utils.h
 *  Autor: Bruno Vale Lourenço
 * =======================================================
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Abre um arquivo através do caminho fornecido e retorna um ponteiro para esse FILE.
 * 
 * @param diretorio Caminho para abertura do arquivo (tipicamente o argv[1]).
 * @param filename Nome do arquivo a ser aberto.
 * @param modo Modo de abertura, 'w' para escrita e 'r' para leitura.
 */
FILE *OpenFile(char *diretorio, char *filename, char modo);

/**
 * Fecha um arquivo
 * 
 * @param f Ponteiro para o FILE a ser fechado.
 */
void CloseFile(FILE *f);

#endif