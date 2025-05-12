#include <stdio.h>
#include <stdlib.h>

#define TAM_MAX 17

void inverte (int n, int* vet)
{
    int j = n - 1, i, aux;

    for(i = 0; i < n; i++)
    {
        aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
        j--;
        
        if(j <= i)
        {
            break;
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

    inverte(TAM_MAX, vet);

    for(int i = 0; i < TAM_MAX; i++)
    {
        printf("%d ", *(vet+i));
    }
    printf("\n");

    if(vet)
    {
        free(vet);
    }

    return 0;
}