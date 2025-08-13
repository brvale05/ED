#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

FILE *OpenFile(char *caminho, char *mode);

void CloseFile(FILE *f);

void FrequencyCount(unsigned int *array, char *caminho);

#endif