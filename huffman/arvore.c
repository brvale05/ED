/** 
 * @file arvore.c
 * @author Bruno Vale e Davi sena
 */

#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"

struct Arv
{

    unsigned char car; // caractere armazenado no nó
    int frequencia;    // frequencia com que esse char aparece
    int folha;         // 1 se o nó for uma folha e 0 caso nao seja uma folha

    Arv *esq;
    Arv *dir;
};

Arv *criaArv_vazia()
{

    return NULL; // cria uma arvore vazia
}

int arv_vazia(Arv *a)
{

    return a == NULL; // 1 se a arvore estiver vazia e 0 se ela possuir algo
}

Arv *insere_Arv(Arv *a, int valorAscii, int freq, int eh_folha)
{

    if (arv_vazia(a))
    {

        a = (Arv *)malloc(sizeof(Arv));

        a->car = valorAscii;
        a->frequencia = freq;
        a->folha = eh_folha;
        a->esq = a->dir = criaArv_vazia();
    }

    return a;
}

Arv *junta_arvs(Arv *a1, Arv *a2)
{

    Arv *tr = criaArv_vazia();
    tr = (Arv *)malloc(sizeof(Arv));
    tr->frequencia = a1->frequencia + a2->frequencia;
    tr->esq = a1;
    tr->dir = a2;
    tr->folha = 0;
    tr->car = '#';

    return tr;
}

int altura_arv(Arv *a)
{

    if (arv_vazia(a))
    {
        return -1;
    }
    else
    {
        int alturaEsq = 0;
        int alturaDir = 0;

        alturaEsq = altura_arv(a->esq);
        alturaDir = altura_arv(a->dir);

        int altura = 0;

        if (alturaDir > alturaEsq)
        {

            altura = alturaDir + 1;
        }
        else
        {

            altura = alturaEsq + 1; // caso a direita nao seja maior que a esquerda, as duas sao iguais ou a esquerda é maior
        }

        return altura;
    }
}

int frequencia_arv(Arv *a)
{

    return a->frequencia;
}

int folha_arv(Arv *a)
{

    return a->folha;
}

unsigned char char_arv(Arv *a)
{

    return a->car;
}

Arv *esqueda_arv(Arv *a)
{

    return a->esq;
}

Arv *direita_arv(Arv *a)
{

    return a->dir;
}

void libera_arv(Arv *a)
{

    if (!arv_vazia(a))
    {
        libera_arv(a->esq);
        libera_arv(a->dir);
        free(a);
    }
}

void bits_arv(Arv *raiz, unsigned int *bits)
{

    if (raiz->folha)
    {
        *bits = *bits + 1 + 8;
        return;
    }

    if (raiz)
    {
        *bits = *bits + 1;
        bits_arv(raiz->esq, bits);
        *bits = *bits + 1;
        bits_arv(raiz->dir, bits);
    }

    return;
}

static char le_bit(char *array_bits, int *index)
{
    return array_bits[*index];
}

static char le_caracter(char *array_bits, int *index)
{
    char car = 0;
    int i;

    for (i = 0; i < 8; i++)
    {
        // Desloca para a esquerda
        car <<= 1;

        if (array_bits[*index] == '1')
        {
            car |= 1; // 'OR' com 1
        }

        *index = *index + 1;
    }

    *index = *index + 1;

    return car;
}

Arv *huffmanTree_descompacta(char *array_bits, int *index, int tam_max)
{
    if (*index >= tam_max)
        return NULL;

    char bit = le_bit(array_bits, index);
    *index = *index + 1;

    if (bit == '1')
    {
        Arv *raiz = criaArv_vazia();

        char car;

        car = le_caracter(array_bits, index);

        raiz = insere_Arv(raiz, car, 0, EH_FOLHA);

        return raiz;
    }
    else
    {

        Arv *raiz = criaArv_vazia();

        raiz = insere_Arv(raiz, 0, 0, !EH_FOLHA);

        raiz->esq = huffmanTree_descompacta(array_bits, index, tam_max);
        raiz->dir = huffmanTree_descompacta(array_bits, index, tam_max);

        return raiz;
    }
}

int eh_unica_arv(Arv *tree)
{
    if(tree->esq == NULL && tree->dir == NULL)
    return 1;

    return 0;
}