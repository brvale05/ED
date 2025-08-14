#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "table.h"
#include "bitmap.h"
#include "pilha.h"
#include "utils.h"

int main(int argc, char **argv)
{
    int id = 0;
    FILE *input_file = OpenFile(argv[1], "rb");

    unsigned int qtdbits_tree = Le_QtdBits(input_file);

    bitmap *tree_bitmap = bitmapDescompacta(qtdbits_tree, input_file);

    char tree_code[qtdbits_tree];

    PreencheBitsArray(tree_code, qtdbits_tree, tree_bitmap);

    Arvore *huffman_tree = DescompactaHuffmanTree(tree_code, &id, qtdbits_tree);

    unsigned int qtdbits_code = Le_QtdBits(input_file);

    bitmap *code_bitmap = bitmapDescompacta(qtdbits_code, input_file);

    int size = TreeHeight(huffman_tree);
    char aux_code[size];

    // cria um vetor de tabelas contendo cada caracter
    Tabela **tabela_codificada = TableVectorConstruct(TAM_MAX);
    BinaryCodeDescompacta(huffman_tree, aux_code, 0, tabela_codificada);

    Arvore *arv_aux = huffman_tree;

    int flag = 0;

    for (int i = 0; i < qtdbits_code; i++)
    {
        unsigned char car;
        car = bitmapGetBit(code_bitmap, i);

        if (car)
        {
            arv_aux = GetRightTree(arv_aux);
            imprimebinario(arv_aux, &flag);
        }
        else
        {
            arv_aux = GetLeftTree(arv_aux);
            imprimebinario(arv_aux, &flag);
        }

        if (flag)
        {
            arv_aux = huffman_tree;
            flag = 0;
        }
    }

    bitmapLibera(tree_bitmap);
    bitmapLibera(code_bitmap);
    TableVectorDestroy(tabela_codificada);
    huffman_tree = BinaryTreeDestroy(huffman_tree);
    CloseFile(input_file);

    return 0;
}