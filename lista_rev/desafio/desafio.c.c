#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAM_MAX 10

int **inverte2(int n, int *vet)
{
    int **vec_resposta = malloc(sizeof(int*)*TAM_MAX);

    int i, j;

    for(i = 0; i < n; i++)
    {
        vec_resposta[i] = &vet[i];
    }

    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(&vet[j] < &vet[i])
            {
                vec_resposta[i] = &vet[j];
            }
        }
    }

    return vec_resposta;
}

int main()
{
    int *vet = malloc(sizeof(int)*TAM_MAX);

    int i;

    for(i = 0; i < TAM_MAX; i++)
    {
        *(vet+i) = i + 1;
    }

    int **vec_resp = inverte2(TAM_MAX, vet);

    for(i = 0; i < TAM_MAX; i++)
    {
        printf("%p ", vec_resp[i]);
    }
    printf("\n");

    if(vet)
    {
        free(vet);
    }

    if(vec_resp)
    {
        free(vec_resp);
    }

    return 0;
}