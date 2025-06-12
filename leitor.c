#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitor.h"

struct Leitor
{
    int id;
    char *nome;
    Lista *pref_list; // lista de generos preferidos
};

Leitor *ReaderConstruct(int id, char *nome, Lista *p_list)
{
    Leitor *l = calloc(1, sizeof(Leitor));

    l->id = id;
    l->nome = nome;
    l->pref_list = p_list;

    return l;
}

void ReaderDestroy(void *data)
{
    if (((Leitor *)data))
    {
        if (((Leitor *)data)->nome)
        {
            free(((Leitor *)data)->nome);
        }

        ListDestroy(((Leitor *)data)->pref_list, CharDestroy);

        free(((Leitor *)data));
    }
}

Leitor *Le_Reader(FILE *r_file, int flag)
{
    Lista *pref_list = ListConstruct();

    int id, n_afinidades, tam;
    char linha[200];
    char *token;
    char *nome;

    if(!flag)
    fgets(linha, 200, r_file);

    while (fgets(linha, 200, r_file) != NULL) 
    {
        linha[strcspn(linha, "\n")] = '\0';

        token = strtok(linha, ";");

        id = atoi(token);

        token = strtok(NULL, ";");

        tam = (strlen(token) + 1);
        nome = malloc(sizeof(char) * tam);
        strcpy(nome, token);

        token = strtok(NULL, ";");
        token = strtok(NULL, ";");

        while (token != NULL)
        {
            tam = (strlen(token) + 1);
            char *afinidade = malloc(sizeof(char) * tam);
            strcpy(afinidade, token);

            ListPushBack(pref_list, afinidade);

            token = strtok(NULL, ";");
        }

        Leitor *l = ReaderConstruct(id, nome, pref_list);

        return l;
    }

    ListDestroy(pref_list, CharDestroy);

    return NULL;
}

void ReaderPrint(void *data)
{
    printf("%d;%s", ((Leitor*)data)->id, ((Leitor*)data)->nome);

    ListPrint(((Leitor*)data)->pref_list, CharPrint);
    printf("\n");
}

