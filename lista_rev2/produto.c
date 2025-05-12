#include <stdio.h>
#include <stdlib.h>
#include "produto.h"
#include <string.h>

struct Produto
{
    char nome[50];
    float preco;
};

Produto* CriaProduto(char *nome, float preco)
{
    Produto *p = malloc(sizeof(Produto));

    //p->nome = malloc(50*sizeof(char));

    strcpy(p->nome, nome);
    p->preco = preco;

    return p;
}

float GetPrecoProduto(Produto *p)
{
    return p->preco;
}

char* GetNomeProduto(Produto *p)
{
    return p->nome;
}

void LiberaProduto(Produto *p)
{
    if(p)
    {
        free(p);
    }
}

Produto* LeProduto()
{
    char nome[50];
    float preco;

    scanf("%*[^A-Za-z]");
    
    scanf("%[^,]", nome);
    scanf("%*[^0-9]");

    scanf("%f", &preco);

    Produto *p = CriaProduto(nome, preco);

    return p;
}

void ImprimeProduto(Produto *p)
{
    printf("%s, valor unitario: %.2f,", p->nome, p->preco);
}