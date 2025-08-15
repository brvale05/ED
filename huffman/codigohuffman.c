#include <stdio.h>
#include <stdlib.h>

#include "codigohuffman.h"
#include "utils.h"

struct CodigoHuffman
{
    char *binary_code;
    char *car;
    int tam;
};

CodigoHuffman *CodigoHuffmanConstruct(char *code, int tam, unsigned char car)
{
    int i;
    CodigoHuffman *h = malloc(sizeof(CodigoHuffman));

    h->binary_code = malloc(sizeof(char) * (tam + 1));

    for (i = 0; i < tam + 1; i++)
    {
        h->binary_code[i] = '\0';
    }

    h->car = malloc(sizeof(char));

    for (i = 0; i < tam; i++)
    {
        h->binary_code[i] = code[i];
    }

    *(h->car) = car;
    h->tam = tam;

    return h;
}

void CodigoHuffmanDestroy(CodigoHuffman *h)
{
    if (h)
    {
        if (h->binary_code)
            free(h->binary_code);

        if (h->car)
            free(h->car);

        free(h);
    }
}

void WriteFileCompactado(bitmap *map, bitmap *tree_map, unsigned int qtdbits_map, unsigned int qtdbits_treemap, char *caminho)
{
    FILE *arquivo_entrada = OpenFile(caminho, "wb", !DESCOMPACTA);

    fwrite(&qtdbits_treemap, sizeof(unsigned int), 1, arquivo_entrada);
    fwrite(bitmapGetContents(tree_map), sizeof(char), (bitmapGetMaxSize(tree_map) + 7) / 8, arquivo_entrada);

    fwrite(&qtdbits_map, sizeof(unsigned int), 1, arquivo_entrada);
    fwrite(bitmapGetContents(map), sizeof(char), (bitmapGetMaxSize(map) + 7) / 8, arquivo_entrada);

    CloseFile(arquivo_entrada);
}

int GetTamHuffmanCode(CodigoHuffman *h)
{
    return h->tam;
}

char GetBitHuffmanCode(CodigoHuffman *h, int id)
{
    return h->binary_code[id];
}


