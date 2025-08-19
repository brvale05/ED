#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "aluno.h"

int main(int argc, char **argv)
{
    FILE *input_file = fopen("entrada.txt", "r");

    Hash turma;
    hash_inicializa(turma);

    char linha[50];
    char nome[30];
    int num;

    fgets(linha, 50, input_file);

    sscanf(linha, "N %d", &num);

    while (fgets(linha, 50, input_file) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';

        sscanf(linha, "%s", nome);

        Aluno *std = hash_insere(turma, nome);
    }

    fclose(input_file);

    char caminho[30];

    char freq;

    for (int i = 1; i <= num; i++)
    {
        sprintf(caminho, "entrada%d.txt", i);
        //printf("%s\n", caminho);

        input_file = fopen(caminho, "r");

        while (fgets(linha, 50, input_file) != NULL)
        {
            linha[strcspn(linha, "\n")] = '\0';

            sscanf(linha, "%s %c", nome, &freq);

            atualiza_frequencia(turma, nome, freq);
        }

        fclose(input_file);
    }

    hash_imprime(turma);

    hash_libera(turma);

    return 0;
}