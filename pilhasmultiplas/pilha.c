#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct 
{
    int base, topo;
} IndicePilha;


struct Pilha
{
    int *vet[TAM_MAX];
    IndicePilha qtd[N_pilhas];
};
