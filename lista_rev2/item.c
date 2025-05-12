#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

struct Item
{
    int qtd;
    Produto *p;
};

Item* CriaItem(int qtd, Produto *p)
{
    Item *i = malloc(sizeof(Item));

    i->qtd = qtd;
    i->p = p;

    return i;
}

void LiberaItem(Item *i)
{
    if(i)
    {
        LiberaProduto(i->p);
        free(i);
    }
}

char* GetNomeItem(Item *i)
{
    return GetNomeProduto(i->p);
}

int GetQuantidadeItem(Item *i)
{
    return i->qtd;
}

float GetValorItem(Item *i)
{
    return GetPrecoProduto(i->p);
}

Item* LeItem()
{
    Produto *p = LeProduto();

    int tam;

    scanf("%*[^0-9]");
    scanf("%d", &tam);

    Item *i = CriaItem(tam, p);

    return i;
}

void ImprimeItem(Item *i)
{
    printf("Item: ");
    ImprimeProduto(i->p);

    printf("quantidade: %d\n", i->qtd);
    
}
