/*
 * =======================================================
 *  Arquivo: livro.c
 *  Autor: Bruno Vale Lourenço
 * =======================================================
 */
#include <stdlib.h>
#include <string.h>

#include "livro.h"

struct Livro
{
    int id;
    char *titulo;
    char *autor;
    char *genero;
    int ano;
};

Livro *BookConstruct(int id, char *titulo, char *autor, char *genero, int ano)
{
    Livro *l = malloc(sizeof(Livro));

    l->id = id;
    l->titulo = titulo;
    l->autor = autor;
    l->genero = genero;
    l->ano = ano;

    return l;
}

Livro *Le_Book(FILE *b_file, int flag)
{
    int id, tam, ano;
    char linha[200];
    char *token, *titulo, *autor, *genero;

    if (!flag)
        fgets(linha, 200, b_file);

    while (fgets(linha, 200, b_file) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';

        token = strtok(linha, ";");

        id = atoi(token);

        token = strtok(NULL, ";");
        tam = (strlen(token) + 1);
        titulo = malloc(sizeof(char) * tam);
        strcpy(titulo, token);

        token = strtok(NULL, ";");
        tam = (strlen(token) + 1);
        autor = malloc(sizeof(char) * tam);
        strcpy(autor, token);

        token = strtok(NULL, ";");
        tam = (strlen(token) + 1);
        genero = malloc(sizeof(char) * tam);
        strcpy(genero, token);

        token = strtok(NULL, ";");

        ano = atoi(token);

        Livro *l = BookConstruct(id, titulo, autor, genero, ano);

        return l;
    }

    return NULL;
}

void BookDestroy(void *data)
{
    if (((Livro *)data))
    {
        if (((Livro *)data)->titulo)
        {
            free(((Livro *)data)->titulo);
        }
        if (((Livro *)data)->autor)
        {
            free(((Livro *)data)->autor);
        }
        if (((Livro *)data)->genero)
        {
            free(((Livro *)data)->genero);
        }

        free(((Livro *)data));
    }
}

void PrintBook(void *data, FILE *stdout_f)
{
    fprintf(stdout_f, "%s", ((Livro*)data)->titulo);
}

int BookCompare(void *data, void *id)
{
    int *chave = (int *)id;

    if (((Livro *)data)->id == *chave)
        return 1;

    return 0;
}

char *GetBookTitle(Livro *b)
{
    return b->titulo;
}

int GetBookId(Livro *b)
{
    return b->id;
}
