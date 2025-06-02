#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

struct Produto
{
    char *nome;
    float preco;
    int codigo;
};

Produto* CriaProduto(char *nome, float preco, int codigo)
{
    //Produto *p = calloc(sizeof(Produto), 1);

    Produto *p = malloc(sizeof(Produto));
    
    p->nome = nome;
    p->preco = preco;
    p->codigo = codigo;

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

int GetCodigoProduto(Produto *p)
{
    return p->codigo;
}

void LiberaProduto(Produto *p)
{
    if(p)
    {
        if(p->nome)
        {
            free(p->nome);
        }
        free(p);
    }
}

Produto* LeProduto()
{
    int cod; 
    float preco; 
    char buffer[50];

    scanf("%*[^0-9]");
    scanf("%d", &cod);
    scanf("%*[^A-Za-z]");
    scanf("%[^;]", buffer);
    scanf("%*[^0-9]");
    scanf("%f", &preco);

    int tam = (strlen(buffer) + 1);

    char *nome = malloc(sizeof(char)*tam);

    strcpy(nome, buffer);

    Produto *p = CriaProduto(nome, preco, cod);

    return p;

}

void ImprimeProduto(Produto *p)
{
    printf("%s, valor unitario: %.2f, codigo: %d\n", p->nome, p->preco, p->codigo);
}