#ifndef LIVRO_H
#define LIVRO_H
#include <stdio.h>

typedef struct Livro Livro;

Livro *BookConstruct(int id, char *titulo, char *autor, char *genero, int ano);

Livro *Le_Book(FILE *b_file, int flag);

void BookDestroy(void *dado);

void BookPrint(void *data);

#endif