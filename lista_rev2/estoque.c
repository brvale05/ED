#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estoque.h"

struct Estoque
{
    int capacidade;
    int tamanho;
    Item **itens;
};

Estoque *CriaEstoque()
{
    Estoque *e = malloc(sizeof(Estoque));

    e->capacidade = 30;

    e->itens = calloc(e->capacidade, sizeof(Item*));

    e->tamanho = 0;

    return e;
}

void LiberaEstoque(Estoque *e)
{
    if(e)
    {
        if(e->itens)
        {
            int i;
            for(i = 0; i < e->capacidade; i++)
            {
                LiberaItem(e->itens[i]);
            }
            free(e->itens);
        }
        free(e);
    }
}

void AtribuiItemEstoque(Estoque *e, Item *item)
{
    if(e->tamanho >= e->capacidade)
    {
        e->capacidade *= 2;
        e->itens = realloc(e->itens, sizeof(Item*)*e->capacidade);
    }

    e->itens[e->tamanho] = item;

    e->tamanho++;
}

Item *GetItemEstoque(Estoque *e, int i)
{
    return e->itens[i];
}

int GetEstoqueTamanho(Estoque *e)
{
    return e->tamanho;
}

Estoque *LeEstoque()
{
    Estoque *e = CriaEstoque();

    printf("Digite a quantidade de itens que deseja cadastrar:\n");

    int n;
    scanf("%d", &n);

    printf("Digite as informacoes dos itens em cada linha:\n");

    for(int i = 0; i < n; i++)
    {
        Item *it = LeItem();
        AtribuiItemEstoque(e, it);
    }

    return e;
}

float CalculaEstoque(Estoque *e)
{
    int i;
    float soma = 0;
    for(i = 0; i < e->tamanho; i++)
    {
        soma = soma + (GetValorItem(GetItemEstoque(e, i)) * GetQuantidadeItem(GetItemEstoque(e, i)));
    }

    return soma;
}

void ImprimeEstoque(Estoque *e)
{
    printf("Estoque: %.2f\n", CalculaEstoque(e));

    int i;
    for(i = 0; i < e->tamanho; i++)
    {
        ImprimeItem(GetItemEstoque(e, i));
    }
}