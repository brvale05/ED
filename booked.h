#ifndef BOOKED_H
#define BOOKED_H

#include "leitor.h"
#include "utils.h"

typedef struct booked tBooked;

/**
 * @brief Função que cria uma estrutura tBooked.
 * 
 * @param caminho String com o diretório para ler os arquivos.
 */
tBooked *BookedConstruct(char *caminho);

/**
 * @brief Função que desaloca uma estrutura tBooked.
 * 
 * @param booked Ponteiro para a booked.
 */
void BookedDestroy(tBooked *booked);

/**
 * @brief Função que lê uma linha de comando do arquivo comandos.txt.
 * 
 * @param comando_file Ponteiro para o arquivo aberto dos comandos.txt.
 * @param vet Vetor com as ID dos comandos.
 * @param flag Flag que lê uma linha a ser descartada.
 */
int Le_Comando(FILE *comando_file, int *vet, int flag);

/**
 * @brief Função que executa os comandos da booked.
 * 
 * @param vet Vetor com as ID dos comandos.
 * @param stdout_file Arquivo de saída.
 * @param booked Ponteiro para a booked.
 */
void ExecutaBooked(int *vet, FILE *stdout_file, tBooked *booked);

/**
 * @brief Função que atualiza as afinidades dos leitores de uma booked.
 * 
 * @param booked Ponteiro para a booked.
 */
void UpdateAfinidades(tBooked *booked);

/**
 * @brief Função que imprime uma booked no arquivo de saída.
 * 
 * @param booked Ponteiro para a booked.
 * @param stdout_file Arquivo de saída.
 */
void BookedPrint(tBooked *booked,FILE *stdout_file);

#endif