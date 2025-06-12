#ifndef LEITOR_H
#define LEITOR_H
#include "lista.h"
#include "livro.h"
#include <stdio.h>

typedef struct Leitor Leitor;

Leitor *ReaderConstruct(int id, char *nome, Lista *p_list);

void ReaderDestroy(void *data);

Leitor *Le_Reader(FILE *r_file, int flag);

void ReaderPrint(void *data);

#endif