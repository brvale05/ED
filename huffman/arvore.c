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

void TreePrint(Arvore *arv)
{
    printf("codigo: %d; caracter: %c; ocorrencias: %d\n", arv->caracter, arv->caracter, arv->num_ocorrencias);
}

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

void GetTreeBitsSize(Arvore *raiz, int id_profundidade, unsigned int *size)
{

    if (raiz->eh_folha)
    {
        *size = *size + 1 + 8;
        // printf("1");
        return;
    }

    if (raiz)
    {
        *size = *size + 1;
        // printf("0");
        GetTreeBitsSize(raiz->esq, id_profundidade + 1, size);
        *size = *size + 1;
        // printf("0");
        GetTreeBitsSize(raiz->dir, id_profundidade + 1, size);
    }

    return;
}

void CompactaHuffmanTree(Arvore *raiz, char *codigo, int id_profundidade, bitmap *tree_bitmap)
{

    if (EhFolha(raiz))
    {
        bitmapAppendLeastSignificantBit(tree_bitmap, '1');

        for(int i = 7; i >= 0; i--)
        {
            int bit = (raiz->caracter >> i) & 1;

            if(bit)
            {
                bitmapAppendLeastSignificantBit(tree_bitmap, '1');
            }
            else
            {
                bitmapAppendLeastSignificantBit(tree_bitmap, '0');
            }
            
        }

        return;
    }

    if (raiz)
    {
        bitmapAppendLeastSignificantBit(tree_bitmap, '0');
        CompactaHuffmanTree(GetLeftTree(raiz), codigo, id_profundidade + 1, tree_bitmap);

        bitmapAppendLeastSignificantBit(tree_bitmap, '0');
        CompactaHuffmanTree(GetRightTree(raiz), codigo, id_profundidade + 1, tree_bitmap);
    }

    return;
}

Arvore *GetLeftTree(Arvore *arv)
{
    return arv->esq;
}

Arvore *GetRightTree(Arvore *arv)
{
    return arv->dir;
}

char GetTreeChar(Arvore *arv)
{
    return arv->caracter;
}

int EhFolha(Arvore *arv)
{
    return arv->eh_folha;
}

