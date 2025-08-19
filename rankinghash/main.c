#include "pais.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE *input_file = fopen("entrada.txt", "r");

    Hash ranking;
    hash_inicializa(ranking);

    char linha[30];
    char nome[4];
    int ouro, prata, bronze, total;

    while (fgets(linha, 30, input_file) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';

        sscanf(linha, "%s %d %d %d %d", nome, &ouro, &prata, &bronze, &total);

        Country *ctry = hash_insere(ranking, nome, ouro, prata, bronze, total);
        //imprime_pais(ctry);
    }

    fclose(input_file);

    int qtd_paises = conta_qtd_paises(ranking);
    
    Country *vetor[qtd_paises];
    adiciona_vetor(ranking, vetor);

    qsort(vetor, qtd_paises, sizeof(Country*), compara_paises);
    escreve_saida(vetor, qtd_paises);

    hash_libera(ranking);

    return 0;
}