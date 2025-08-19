#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pais.h"

struct Country
{
    char nome[4];
    int ouro;
    int prata;
    int bronze;
    int total;
    Country *prox;
};

void hash_inicializa(Hash ranking)
{
    for (int i = 0; i < TAM_MAX; i++)
    {
        ranking[i] = NULL;
    }
}

Country *hash_insere(Hash ranking, char *nome, int ouro, int prata, int bronze, int total)
{
    int h = hash_id(nome);

    Country *ctry = ranking[h];

    while (ctry != NULL)
    {
        if (!strcmp(ctry->nome, nome))
            break;

        ctry = ctry->prox;
    }

    if (ctry == NULL)
    {
        ctry = malloc(sizeof(Country));

        ctry->prox = ranking[h];
        ranking[h] = ctry;
    }

    strcpy(ctry->nome, nome);
    ctry->ouro = ouro;
    ctry->prata = prata;
    ctry->bronze = bronze;
    ctry->total = total;

    return ctry;
}

int hash_id(char *chave)
{
    int soma = 0;

    for (int i = 0; chave[i] != '\0'; i++)
        soma += (int)chave[i];

    return (soma % 4);
}

void hash_libera(Hash ranking)
{
    if (ranking)
    {
        int i;
        for (i = 0; i < TAM_MAX; i++)
        {
            if (ranking[i])
            {
                Country *antes;
                Country *atual = ranking[i];

                while (atual != NULL)
                {
                    antes = atual;
                    atual = atual->prox;
                    free(antes);
                }
            }
        }
    }
}

int conta_qtd_paises(Hash ranking)
{
    int i, soma = 0;

    for(i = 0; i < TAM_MAX; i++)
    {
        Country *aux = ranking[i];

        while (aux != NULL)
        {
            soma++;
            aux = aux->prox;
        }
        
    }

    return soma;

}

int compara_paises(const void *p1, const void *p2)
{

    if((*(Country **)p1)->ouro != (*(Country **)p2)->ouro)
    {
        return (*(Country **)p2)->ouro - (*(Country **)p1)->ouro;
    }

    if((*(Country **)p1)->prata != (*(Country **)p2)->prata)
    {
        return (*(Country **)p2)->prata - (*(Country **)p1)->prata;
    }

    if((*(Country **)p1)->bronze != (*(Country **)p2)->bronze)
    {
        return (*(Country **)p2)->bronze - (*(Country **)p1)->bronze;
    }

    return strcmp((*(Country **)p1)->nome, (*(Country **)p2)->nome);
}

void imprime_pais(Country *ctry)
{
    printf("%s %d %d %d %d\n", ctry->nome, ctry->ouro, ctry->prata, ctry->bronze, ctry->total);
}

void adiciona_vetor(Hash ranking, Country **vetor)
{
    int i, j = 0;

    for(i = 0; i < TAM_MAX; i++)
    {
        Country *aux = ranking[i];

        while (aux != NULL)
        {
            vetor[j] = aux;
            j++;
            aux = aux->prox;
        }
        
    }
}

void escreve_saida(Country **vetor, int tam)
{
    FILE *output = fopen("saida.txt", "w");

    for(int i = 0; i < tam; i++)
    {
        fprintf(output,"%s %d %d %d %d\n", vetor[i]->nome, vetor[i]->ouro, vetor[i]->prata, vetor[i]->bronze, vetor[i]->total);
    }

    fclose(output);
}
