#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supermercado.h"

struct Supermercado
{
    Filial **filiais;
    char nome[50];
    int tamanho;
    int capacidade;
    float valorTotal;
};

Supermercado *CriaSupermercado(char *nome)
{
    Supermercado *s = malloc(sizeof(Supermercado));

    s->capacidade = 20;

    s->filiais = calloc(s->capacidade, sizeof(Filial*));
  
    strcpy(s->nome, nome);

    
    s->tamanho = 0;
    s->valorTotal = 0;

    return s;
}

void LiberaSupermercado(Supermercado *s)
{
    if (s)
    {
        if (s->filiais)
        {
            int i;
            for (i = 0; i < s->capacidade; i++)
            {
                LiberaFilial(s->filiais[i]);
            }
            free(s->filiais);
        }
        free(s);
    }
}

void AtribuiFilial(Supermercado *s, Filial *data)
{
    if (s->tamanho >= s->capacidade)
    {
        s->capacidade *= 2;
        s->filiais = realloc(s->filiais, sizeof(Filial *) * s->capacidade);
    }

    s->filiais[s->tamanho] = data;
    s->tamanho++;
}

Filial *GetFilial(Supermercado *s, int i)
{
    return s->filiais[i];
}

float GetValorTotalEstoques(Supermercado *s)
{
    return s->valorTotal;
}

void CalculaValorTotalSup(Supermercado *s)
{
    int i;
    s->valorTotal = 0;
    for (i = 0; i < s->tamanho; i++)
    {
        s->valorTotal = s->valorTotal + CalculaValorEstoqueFilial(GetFilial(s, i));
    }
}

void ImprimeSupermercado(Supermercado *s)
{
    CalculaValorTotalSup(s);
    printf("Nome: %s, Estoque Total: %.2f\n", s->nome, s->valorTotal);

    int i;
    for (i = 0; i < s->tamanho; i++)
    {
        ImprimeFilial(GetFilial(s, i));
    }
}