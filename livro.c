#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

struct Livro
{
    int id;
    char titulo[50];
    char autor[50];
    char genero[50];
    int ano;
};

void DesalocaLivro(void *dado)
{
    if (((Livro *)dado))
    {
        free(((Livro *)dado));
    }
}