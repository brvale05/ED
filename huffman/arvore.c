#include <stdio.h>
#include <stdlib.h>

#include "bitmap.h"
#include "arvore.h"

struct Arvore
{
    char caracter;
    int num_ocorrencias;
    int eh_folha; // 1 para folha e 0 caso nao seja
    Arvore *esq;
    Arvore *dir;
};

Arvore *TreeConstruct(int codigo, int num_eventos, int ehfolha)
{
    Arvore *a = malloc(sizeof(Arvore));

    a->caracter = codigo;
    a->num_ocorrencias = num_eventos;
    a->eh_folha = ehfolha;
    a->esq = NULL;
    a->dir = NULL;

    return a;
}

Arvore *TreePushBack(Arvore *raiz1, Arvore *raiz2)
{
    Arvore *arv = TreeConstruct(38, raiz1->num_ocorrencias + raiz2->num_ocorrencias, !EH_FOLHA);
    arv->esq = raiz1;
    arv->dir = raiz2;

    return arv;
}

// void TreePrint(Arvore *arv)
// {
//     printf("codigo: %d; caracter: %c; ocorrencias: %d\n", arv->caracter, arv->caracter, arv->num_ocorrencias);
// }

void BinaryTreePrint(Arvore *arv)
{
    if (arv)
    {
        BinaryTreePrint(arv->esq);
        if (arv->eh_folha)
        {
            printf("codigo: %d; caracter: %c; ocorrencias: %d\n", arv->caracter, arv->caracter, arv->num_ocorrencias);
        }
        BinaryTreePrint(arv->dir);
    }
}

Arvore *BinaryTreeDestroy(Arvore *arv)
{
    if (arv)
    {
        BinaryTreeDestroy(arv->esq);
        BinaryTreeDestroy(arv->dir);
        free(arv);
    }

    return NULL;
}

int TreesCompare(const void *t1, const void *t2)
{
    if ((*(Arvore **)t1)->num_ocorrencias > (*(Arvore **)t2)->num_ocorrencias)
    {
        return 1;
    }
    else if ((*(Arvore **)t1)->num_ocorrencias < (*(Arvore **)t2)->num_ocorrencias)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int TreeHeight(Arvore *raiz)
{
    if (raiz == NULL)
    {
        return -1;
    }

    int alturaEsquerda = TreeHeight(raiz->esq);
    int alturaDireita = TreeHeight(raiz->dir);

    int maiorAltura;
    if (alturaEsquerda > alturaDireita)
    {
        maiorAltura = alturaEsquerda;
    }
    else
    {
        maiorAltura = alturaDireita;
    }
    return maiorAltura + 1;
}

bitmap *BinaryCode(Arvore *raiz, int *array, int id)
{
    if(raiz == NULL)
    {
        return;
    }
}
