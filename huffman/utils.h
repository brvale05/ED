#ifndef UTILS_H
#define UTILS_H

#define COMPACTA 1

#include <stdio.h>

FILE *OpenFile(char *caminho, char *mode, int flag_tipo);

void CloseFile(FILE *f);

void FrequencyCount(unsigned int *array, char *caminho);

#endif