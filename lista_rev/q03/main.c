#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 20  

int pares (int n, int* vet)
{
    int soma = 0;

    for(int i = n; i >= 0; i--)
    {
        if(*(vet+i)%2 == 0)        
        {
            return pares(n - 1, vet) + 1;
        }
        else
        {
            return pares(n - 1, vet);
        }
    }
}

int main()
{
    int *vet = malloc(sizeof(int)*TAM_MAX);

    for(int i = 0; i < TAM_MAX; i++)
    {
        *(vet+i) = i + 1;
    }

    int resp = pares(TAM_MAX, vet);

    printf("quantidade de pares = %d\n", resp);

    if(vet)
    {
        free(vet);
    }

    return 0;
}