#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "table.h"

struct Tabela
{
    char *binary_code;
    char *car;
};

Tabela *TabelaConstruct(char *code, int code_size, char car)
{
    int i;
    Tabela *t = malloc(sizeof(Tabela));

    t->binary_code = malloc(sizeof(char) * (code_size + 1));

    for(i = 0; i < code_size + 1; i++)
    {
        t->binary_code[i] = '\0';
    }

    t->car = malloc(sizeof(char));

    for(i = 0; i < code_size; i++)
    {
        t->binary_code[i] = code[i];
    }

    *(t->car) = car;

    return t;
}

Tabela **TableVectorConstruct(int tam)
{
    Tabela **tabela_codificada = malloc(sizeof(Tabela*) * tam);

    int i;
    for(i = 0; i < tam; i++)
    {
        tabela_codificada[i] = NULL;
    }

    return tabela_codificada;
}

void VectorPushBack(Tabela **vector, Tabela *data, int id)
{
    vector[id] = data;
}

void TableDestroy(Tabela *t)
{
    if(t)
    {
        if(t->binary_code)
        free(t->binary_code);

        if(t->car)
        free(t->car);

        free(t);
    }
}

void TableVectorDestroy(Tabela **vector)
{
    if(vector)
    {
        int i;
        for(i = 0; i < 256; i++)
        {
            TableDestroy(vector[i]);
        }
        free(vector);
    }
}

void PrintTable(Tabela **vector)
{
    int i;
    for(i = 0; i < 256; i++)
    {
        if(vector[i] != NULL)
        {
            printf("cod: %s, car: %c\n", vector[i]->binary_code, *vector[i]->car);
        }
    }
}

void BinaryCodeConstruct(Arvore *raiz, char *codigo, int id_profundidade, Tabela **vector, unsigned int *array_de_frequencias, unsigned int *qtd_bits)
{

    if (EhFolha(raiz))
    {
        char car = GetTreeChar(raiz);
        int codigo_ascii = car;

        //construindo um vetor contendo o codigo binario compactado de cada caracter
        Tabela *t = TabelaConstruct(codigo, id_profundidade, car);
        VectorPushBack(vector, t, codigo_ascii);

        //atualizando quantidade de bits
        *qtd_bits = *qtd_bits + (array_de_frequencias[codigo_ascii] * id_profundidade);
        
        return;
    }

    if (raiz)
    {
        codigo[id_profundidade] = '0';
        BinaryCodeConstruct(GetLeftTree(raiz), codigo, id_profundidade + 1, vector, array_de_frequencias, qtd_bits);

        codigo[id_profundidade] = '1';
        BinaryCodeConstruct(GetRightTree(raiz), codigo, id_profundidade + 1, vector, array_de_frequencias, qtd_bits);
    }

    return;
}

void UpdateMapaDeBits(Tabela **vector, char *caminho, bitmap *map)
{    
    FILE *input_file = OpenFile(caminho, "r");

    char car;

    Tabela *aux;

    int codigo_ascii;

    while (!feof(input_file))
    {
        fread(&car, sizeof(char), 1, input_file);

        if(feof(input_file))
        break;

        codigo_ascii = car;
       
        aux = vector[codigo_ascii];

        for(int i = 0; aux->binary_code[i] != '\0'; i++)
        {
            unsigned char c = aux->binary_code[i];
            bitmapAppendLeastSignificantBit(map, c);
        }

    }

    CloseFile(input_file);
}

void BinaryFileWrite(bitmap *map, bitmap *tree_map, unsigned int qtdbits_map, unsigned int qtdbits_treemap, char *caminho)
{
    FILE *arquivo_entrada = OpenFile(caminho, "wb");

    fwrite(&qtdbits_treemap, sizeof(unsigned int), 1, arquivo_entrada);
    fwrite(bitmapGetContents(tree_map), sizeof(char), (bitmapGetMaxSize(tree_map) + 7)/8, arquivo_entrada);

    fwrite(&qtdbits_map, sizeof(unsigned int), 1, arquivo_entrada);
    fwrite(bitmapGetContents(map), sizeof(char), (bitmapGetMaxSize(map) + 7)/8, arquivo_entrada);

    CloseFile(arquivo_entrada);
}

