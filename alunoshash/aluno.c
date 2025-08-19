#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"

struct Aluno
{
    char *nome;
    int faltas;
    int presencas;
    Aluno *prox;
};

Aluno *hash_insere(Hash turma, char *nome)
{
    int h = hash(nome);

    Aluno *a = turma[h];

    while (a != NULL)
    {
        if (!strcmp(a->nome, nome))
            break;

        a = a->prox;
    }

    if (a == NULL)
    {
        a = malloc(sizeof(Aluno));

        a->prox = turma[h];
        turma[h] = a;
    }

    a->nome = strdup(nome);
    a->faltas = 0;
    a->presencas = 0;

    return a;
}

void hash_inicializa(Hash turma)
{
    for (int i = 0; i < TAM_MAX; i++)
    {
        turma[i] = NULL;
    }
}

int hash(char *chave)
{
    int i, soma = 0;
    for (i = 0; i < strlen(chave); i++)
    {
        soma += (int)chave[i];
    }

    return (soma % strlen(chave));
}

void hash_libera(Hash turma)
{
    if (turma)
    {
        int i;
        for (i = 0; i < TAM_MAX; i++)
        {
            if (turma[i])
            {
                Aluno *antes;
                Aluno *atual = turma[i];

                while (atual != NULL)
                {
                    antes = atual;
                    atual = atual->prox;
                    free(antes->nome);
                    free(antes);
                }
            }
        }
    }
}

void imprime_aluno(Aluno *a, FILE *output)
{
    fprintf(output, "%s %dP %dF\n", a->nome, a->presencas, a->faltas);
}

void atualiza_frequencia(Hash turma, char *nome, char frequencia)
{
    int h = hash(nome);

    Aluno *aux = turma[h];

    while (aux != NULL)
    {
        if (!strcmp(aux->nome, nome))
            break;

        aux = aux->prox;
    }

    if (aux == NULL)
        return;

    if (frequencia == 'P')
    {
        aux->presencas++;
    }
    else
    {
        aux->faltas++;
    }
}

void hash_imprime(Hash turma)
{
    FILE *output = fopen("saida.txt", "w");

    int i;
    for (i = 0; i < TAM_MAX; i++)
    {
        if (turma[i])
        {
            Aluno *atual = turma[i];

            while (atual != NULL)
            {
                imprime_aluno(atual, output);
                atual = atual->prox;
            }
        }
    }

    fclose(output);

}