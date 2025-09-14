/** 
 * @file codificacao.c
 * @author Bruno Vale e Davi sena
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codificacao.h"

// codigo de cada caractere
struct Cod
{
    unsigned char c;
    char *codigo;
};

void inicializa_vetor_COD(Cod **tabela_cod)
{

    for (int i = 0; i < 256; i++)
    {

        tabela_cod[i] = (Cod *)malloc(sizeof(Cod));
        tabela_cod[i]->codigo = NULL;
        tabela_cod[i]->c = 0;
    }
}

Cod **vetor_codificacao(int tamanho)
{

    Cod **vetor = malloc(sizeof(Cod *) * tamanho);

    return vetor;
}

void gera_codigo(Arv *a, char *codigo, int eh_unicaArvore, int profundidade, Cod **tabela)
{
    if (arv_vazia(a))
    {

        return;
    }

    if (folha_arv(a))
    { // caso o nó seja uma folha, atribui o codigo a ela

        unsigned char c = char_arv(a);
        int ascii = c;
        tabela[ascii]->c = c;

        codigo[profundidade] = '\0'; // finaliza a string

        if (eh_unicaArvore)
        {
            codigo[profundidade] = '1';
            codigo[profundidade + 1] = '\0'; // finaliza a string
        }

        tabela[ascii]->codigo = strdup(codigo);
    }
    else
    { // caso o nó nao seja uma folha

        // vai para o nó da esquerda e adiciona 0 no codigo
        codigo[profundidade] = '0';
        gera_codigo(esqueda_arv(a), codigo, eh_unicaArvore, profundidade + 1, tabela);

        // vai para o nó da direita e adicona 1 no codigo
        codigo[profundidade] = '1';
        gera_codigo(direita_arv(a), codigo, eh_unicaArvore, profundidade + 1, tabela);
    }
}

int conta_qntd_bits_HUFF(Cod **tabela_cod, unsigned char car)
{

    int totalBits = 0;
    int ascii = 0;

    ascii = car;

    char *string;

    string = strdup(tabela_cod[ascii]->codigo);

    for (int i = 0; string[i] != '\0'; i++)
    {

        totalBits++;
    }

    free(string);

    return totalBits;
}

char *retorna_codigo_tabelaCOD(Cod **tabela_cod, int n)
{

    return tabela_cod[n]->codigo;
}

void imprime_tabela(Cod **tabela, int num_chars)
{
    printf("\n--- Tabela de Codificacao de Huffman ---\n");
    for (int i = 0; i < num_chars; i++)
    {

        if (tabela[i]->codigo != NULL)
        {

            printf("Caractere: '%c' | Codigo: %s\n", tabela[i]->c, tabela[i]->codigo);
        }
    }
    printf("---------------------------------------\n");
}

void desaloca_vetorTabela_cod(Cod **tabela_cod)
{

    if (tabela_cod == NULL)
    {

        return; // nao faz nada
    }
    else
    {

        for (int i = 0; i < 256; i++)
        {

            if (tabela_cod[i] != NULL)
            {

                if (tabela_cod[i]->codigo != NULL)
                {

                    free(tabela_cod[i]->codigo);
                }
                free(tabela_cod[i]);
            }
        }

        free(tabela_cod);
    }
}

Cod *cod_construct(char *codigo, int tam, unsigned char car)
{
    int i;
    Cod *h = malloc(sizeof(Cod));

    h->codigo = malloc(sizeof(char) * (tam + 1));

    for (i = 0; i < tam + 1; i++)
    {
        h->codigo[i] = '\0';
    }

    for (i = 0; i < tam; i++)
    {
        h->codigo[i] = codigo[i];
    }

    h->c = car;

    return h;
}

void tabelaCod_reconstruct(Arv *raiz, char *codigo, int id_profundidade, Cod **tabela_cod, int unica_arv)
{

    if (folha_arv(raiz))
    {
        unsigned char car = char_arv(raiz);
        unsigned int codigo_ascii = car;

        if (unica_arv)
        {
            codigo[id_profundidade] = '1';
        }

        Cod *h = cod_construct(codigo, id_profundidade, car);

        tabela_cod[codigo_ascii] = h;

        return;
    }

    if (raiz)
    {
        codigo[id_profundidade] = '0';
        tabelaCod_reconstruct(esqueda_arv(raiz), codigo, id_profundidade + 1, tabela_cod, unica_arv);

        codigo[id_profundidade] = '1';
        tabelaCod_reconstruct(direita_arv(raiz), codigo, id_profundidade + 1, tabela_cod, unica_arv);
    }

    return;
}
