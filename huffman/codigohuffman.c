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



// CodigoHuffman **TableVectorConstruct(int tam)
// {
//     CodigoHuffman **tabela_codificada = malloc(sizeof(CodigoHuffman *) * tam);

//     int i;
//     for (i = 0; i < tam; i++)
//     {
//         tabela_codificada[i] = NULL;
//     }

//     return tabela_codificada;
// }

// void VectorPushBack(CodigoHuffman **vector, CodigoHuffman *data, int id)
// {
//     vector[id] = data;
// }



// void TableVectorDestroy(CodigoHuffman **vector)
// {
//     if (vector)
//     {
//         int i;
//         for (i = 0; i < 256; i++)
//         {
//             TableDestroy(vector[i]);
//         }
//         free(vector);
//     }
// }

// void PrintTable(CodigoHuffman **vector)
// {
//     int i;
//     for (i = 0; i < 256; i++)
//     {
//         if (vector[i] != NULL)
//         {
//             printf("cod: %s, car: %c\n", vector[i]->binary_code, *vector[i]->car);
//         }
//     }
// }

// void BinaryCodeConstruct(Arvore *raiz, char *codigo, int id_profundidade, CodigoHuffman **vector, unsigned int *array_de_frequencias, unsigned int *qtd_bits)
// {

//     if (EhFolha(raiz))
//     {
//         char car = GetTreeChar(raiz);
//         int codigo_ascii = car;

//         // construindo um vetor contendo o codigo binario compactado de cada caracter
//         CodigoHuffman *h = TabelaConstruct(codigo, id_profundidade, car);
//         VectorPushBack(vector, h, codigo_ascii);

//         // atualizando quantidade de bits
//         *qtd_bits = *qtd_bits + (array_de_frequencias[codigo_ascii] * id_profundidade);

//         return;
//     }

//     if (raiz)
//     {
//         codigo[id_profundidade] = '0';
//         BinaryCodeConstruct(GetLeftTree(raiz), codigo, id_profundidade + 1, vector, array_de_frequencias, qtd_bits);

//         codigo[id_profundidade] = '1';
//         BinaryCodeConstruct(GetRightTree(raiz), codigo, id_profundidade + 1, vector, array_de_frequencias, qtd_bits);
//     }

//     return;
// }

// void UpdateMapaDeBits(CodigoHuffman **vector, char *caminho, bitmap *map)
// {
//     FILE *input_file = OpenFile(caminho, "rb", 0);

//     char car;

//     CodigoHuffman *aux;

//     int codigo_ascii;

//     while (!feof(input_file))
//     {
//         fread(&car, sizeof(char), 1, input_file);

//         if (feof(input_file))
//             break;

//         codigo_ascii = car;

//         aux = vector[codigo_ascii];

//         for (int i = 0; aux->binary_code[i] != '\0'; i++)
//         {
//             unsigned char c = aux->binary_code[i];
//             bitmapAppendLeastSignificantBit(map, c);
//         }
//     }

//     CloseFile(input_file);
// }



// void BinaryCodeDescompacta(Arvore *raiz, char *codigo, int id_profundidade, CodigoHuffman **vector)
// {

//     if (EhFolha(raiz))
//     {
//         char car = GetTreeChar(raiz);
//         int codigo_ascii = car;

//         // construindo um vetor contendo o codigo binario compactado de cada caracter
//         CodigoHuffman *h = TabelaConstruct(codigo, id_profundidade, car);
//         VectorPushBack(vector, h, codigo_ascii);

//         return;
//     }

//     if (raiz)
//     {
//         codigo[id_profundidade] = '0';
//         BinaryCodeDescompacta(GetLeftTree(raiz), codigo, id_profundidade + 1, vector);

//         codigo[id_profundidade] = '1';
//         BinaryCodeDescompacta(GetRightTree(raiz), codigo, id_profundidade + 1, vector);
//     }

//     return;
// }


