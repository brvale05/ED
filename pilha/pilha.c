#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct Pilha
{
    int **vet;
    int topo1, topo2;
};


Pilha *PilhaConstruct()
{
    Pilha *p = malloc(sizeof(Pilha));
    p->topo1 = -1;
    p->topo2 = TAM_MAX;

    p->vet = calloc(TAM_MAX, sizeof(int*));

    return p;
}

void PilhaDestroy(Pilha *p)
{
    if(p)
    {
        if(p->vet)
        {
            int i;
            for(i = 0; i < TAM_MAX; i++)
            {
                if(p->vet[i])
                free(p->vet[i]);
            }
            free(p->vet);
        }
        free(p);
    }
}

void PilhaPush1(Pilha *p, int codigo)
{
    int aux = codigo;

    if(!Cheia(p))
    {
        int *valor = malloc(sizeof(int));

        *valor = aux;

        p->topo1++;
        p->vet[p->topo1] = valor;
    }
}

void PilhaPush2(Pilha *p, int codigo)
{
    int aux = codigo;

    if(!Cheia(p))
    {
        int *valor = malloc(sizeof(int));

        *valor = aux;

        p->topo2--;
        p->vet[p->topo2] = valor;
    }
}

void PilhaRemove1(Pilha *p)
{
    if(p->topo1 < 0)
    {
        printf("Pilha Vazia!\n");
    }
    else
    {
        if(p->vet[p->topo1])
        free(p->vet[p->topo1]);

        p->vet[p->topo1] = NULL;

        p->topo1--;
    }
}

void PilhaRemove2(Pilha *p)
{
    if(p->topo2 == TAM_MAX)
    {
        printf("Pilha Vazia!\n");
    }
    else
    {
        if(p->vet[p->topo2])
        free(p->vet[p->topo2]);

        p->vet[p->topo2] = NULL;

        p->topo2++;
    }
}

void PilhaPrint(Pilha *p)
{
    int i;
    printf("================\n");
    for(i = 0; i <= p->topo1; i++)
    {
        if(p->vet[i])
        printf("CODIGO: %d\n", *(p->vet[i]));
    }

    for(i = TAM_MAX - 1; i >= p->topo2; i--)
    {
        if(p->vet[i])
        printf("CODIGO: %d\n", *(p->vet[i]));
    }
    printf("================\n"); 
}

int Cheia(Pilha *p)
{
    if(p->topo1 == p->topo2 - 1)
    {
        printf("Pilha Cheia!\n");
        return 1;
    }

    return 0;

}