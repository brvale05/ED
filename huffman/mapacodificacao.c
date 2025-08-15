#include <stdio.h>
#include <stdlib.h>

#include "mapacodificacao.h"
#include "codigohuffman.h"

struct MapaCodificacao
{
    CodigoHuffman **tabela;
    int tam;
};

MapaCodificacao *MapaCodificacaoConstruct(int tam)
{
    MapaCodificacao *map = malloc(sizeof(MapaCodificacao));

    map->tabela = malloc(sizeof(CodigoHuffman *) * tam);

    int i;
    for (i = 0; i < tam; i++)
    {
        map->tabela[i] = NULL;
    }

    return map;
}

void MapPushBack(MapaCodificacao *map, CodigoHuffman *item_map, unsigned int id)
{
    map->tabela[id] = item_map;
}

void MapDestroy(MapaCodificacao *map)
{
    if (map)
    {
        if (map->tabela)
        {
            int i;
            for (i = 0; i < 256; i++)
            {
                CodigoHuffmanDestroy(map->tabela[i]);
            }
        }
        free(map->tabela);
    }
    free(map);
}

void BinaryCodeConstruct(Arvore *raiz, char *codigo, int id_profundidade, MapaCodificacao *map, unsigned int *array_de_frequencias, unsigned int *qtd_bits)
{

    if (EhFolha(raiz))
    {
        unsigned char car = GetTreeChar(raiz);
        int codigo_ascii = car;

        CodigoHuffman *h = CodigoHuffmanConstruct(codigo, id_profundidade, car);

        MapPushBack(map, h, codigo_ascii);

        // atualizando quantidade de bits
        *qtd_bits = *qtd_bits + (array_de_frequencias[codigo_ascii] * id_profundidade);

        return;
    }

    if (raiz)
    {
        codigo[id_profundidade] = '0';
        BinaryCodeConstruct(GetLeftTree(raiz), codigo, id_profundidade + 1, map, array_de_frequencias, qtd_bits);

        codigo[id_profundidade] = '1';
        BinaryCodeConstruct(GetRightTree(raiz), codigo, id_profundidade + 1, map, array_de_frequencias, qtd_bits);
    }

    return;
}

void BitMapCompacta(MapaCodificacao *codifica_map, char *caminho, bitmap *map)
{
    FILE *input_file = OpenFile(caminho, "rb", !DESCOMPACTA);

    unsigned char car;

    CodigoHuffman *aux;

    int codigo_ascii;

    while (!feof(input_file))
    {
        fread(&car, sizeof(unsigned char), 1, input_file);

        if (feof(input_file))
            break;

        codigo_ascii = car;

        aux = codifica_map->tabela[codigo_ascii];

        for (int i = 0; i < GetTamHuffmanCode(aux); i++)
        {
            unsigned char c = GetBitHuffmanCode(aux, i);
            bitmapAppendLeastSignificantBit(map, c);
        }
    }

    CloseFile(input_file);
}

void BinaryCodeDescompacta(Arvore *raiz, char *codigo, int id_profundidade, MapaCodificacao *map)
{

    if (EhFolha(raiz))
    {
        unsigned char car = GetTreeChar(raiz);
        unsigned int codigo_ascii = car;

        CodigoHuffman *h = CodigoHuffmanConstruct(codigo, id_profundidade, car);
        MapPushBack(map, h, codigo_ascii);
        return;
    }

    if (raiz)
    {
        codigo[id_profundidade] = '0';
        BinaryCodeDescompacta(GetLeftTree(raiz), codigo, id_profundidade + 1, map);

        codigo[id_profundidade] = '1';
        BinaryCodeDescompacta(GetRightTree(raiz), codigo, id_profundidade + 1, map);
    }

    return;
}

void OriginalFileReconstruct_Aux(Arvore *raiz, int *flag, FILE *output_file)
{

    if (EhFolha(raiz))
    {
        char c = GetTreeChar(raiz);

        fwrite(&c, sizeof(char), 1, output_file);
        *flag = *flag + 1;
    }

    return;
}

void OriginalFileReconstruct(Arvore *raiz, bitmap *bm, char *caminho)
{
    FILE *output_file = OpenFile(caminho, "wb", DESCOMPACTA);
    Arvore *arv_aux = raiz;

    int flag = 0;

    for (int i = 0; i < bitmapGetLength(bm); i++)
    {
        unsigned char car;
        car = bitmapGetBit(bm, i);

        if (car)
        {
            arv_aux = GetRightTree(arv_aux);
            OriginalFileReconstruct_Aux(arv_aux, &flag, output_file);
        }
        else
        {
            arv_aux = GetLeftTree(arv_aux);
            OriginalFileReconstruct_Aux(arv_aux, &flag, output_file);
        }

        if (flag)
        {
            arv_aux = raiz;
            flag = 0;
        }
    }

    CloseFile(output_file);

}