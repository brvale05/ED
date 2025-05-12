#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filial.h"

struct Filial
{
    char nome[50];
    Estoque *est;
};

Filial *CriaFilial(char *nome)
{
    Filial *f = malloc(sizeof(Filial));
    
    //f->nome = malloc(sizeof(char)*30);

    strcpy(f->nome, nome);

    return f;
}

void LiberaFilial(Filial *f)
{
    if (f)
    {
        LiberaEstoque(f->est);
        free(f);
    }
}

void AtribuiEstoque(Filial *f, Estoque *e)
{
    f->est = e;
}

Filial *LeFilial()
{
    char nome[30];

    scanf("%*[^A-Za-z]");

    scanf("%[^\n]", nome);
    scanf("%*c");

    Filial *f = CriaFilial(nome);

    return f;
}

float CalculaValorEstoqueFilial(Filial *f)
{
    return CalculaEstoque(f->est);
}

void ImprimeFilial(Filial *f)
{
    printf("Filial: %s\n", f->nome);

    ImprimeEstoque(f->est);
}
