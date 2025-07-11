#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct Lista Lista;

struct Lista
{
    Lista *prox;
    Lista *ant;
    int id;
};


struct Fila
{
    Lista *inicio;
    Lista *fim;    
};


Fila *FilaConstruct()
{
    Fila *f = malloc(sizeof(Fila));

    f->inicio = NULL;
    f->fim = NULL;

    return f;
}

void FilaDestroy(Fila *f)
{
    Lista *antes = NULL;
    Lista *atual = f->inicio;

    if(f)
    {
        while (atual != NULL)
        {
            antes = atual;
            atual = atual->prox;
            free(antes);
        }

        free(f);
        
    }
}

//insere no final
void FilaPushBack(Fila *f, int codigo)
{
    Lista *novo = malloc(sizeof(Lista));
    novo->id = codigo;
    novo->prox = NULL;
    novo->ant = NULL;

    //se tiver vazia
    if(f->inicio == NULL)
    {
        f->inicio = f->fim = novo;
    }
    else
    {
        f->fim->prox = novo;
        novo->ant = f->fim;
        f->fim = novo;
    }
}

//retira do inicio
void FilaRemove(Fila *f)
{
    Lista *aux = f->inicio;

    if(f->inicio == NULL)
    {
        printf("Fila Vazia!\n");
        return;
    }

    f->inicio = f->inicio->prox;
    f->inicio->ant = NULL;

    free(aux);
}

void FilaPrint(Fila *f)
{
    Lista *aux = f->inicio;

    printf("================\n");
    while (aux != NULL)
    {
        printf("CODIGO: %d\n", aux->id);
        aux = aux->prox;
    }
    printf("================\n");
}