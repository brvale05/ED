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

int ReaderCompare(void *data, int id);

Lista *GetLidosList(Leitor *l);

Lista *GetWishList(Leitor *l);

Lista *GetRecList(Leitor *l);

char *GetReaderName(Leitor *l);



#endif