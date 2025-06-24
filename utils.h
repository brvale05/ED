#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

FILE *OpenFile(char *diretorio, char *filename, char modo);

void CloseFile(FILE *f);

#endif