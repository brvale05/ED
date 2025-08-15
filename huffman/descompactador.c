#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mapacodificacao.h"
#include "pilha.h"

int main(int argc, char **argv)
{
    int id = 0;
    FILE *input_file = OpenFile(argv[1], "rb", !DESCOMPACTA);

    unsigned int tree_qtdbits = Le_QtdBits(input_file);
    bitmap *tree_bitmap = BitMapDescompacta(tree_qtdbits, input_file);

    unsigned int text_qtdbits = Le_QtdBits(input_file);
    bitmap *text_bitmap = BitMapDescompacta(text_qtdbits, input_file);

    CloseFile(input_file);

    char tree_code[tree_qtdbits];
    PreencheBitsArray(tree_code, tree_qtdbits, tree_bitmap);
    Arvore *huffman_tree = DescompactaHuffmanTree(tree_code, &id, tree_qtdbits);

    int tree_height = TreeHeight(huffman_tree);
    char aux_array[tree_height];
    
    //cria um mapa de codificacao
    MapaCodificacao *map_decodifica = MapaCodificacaoConstruct(TAM_MAX_MAPA);
    BinaryCodeDescompacta(huffman_tree, aux_array, 0, map_decodifica);

    OriginalFileReconstruct(huffman_tree, text_bitmap, argv[1]);

    bitmapLibera(tree_bitmap);
    bitmapLibera(text_bitmap);
    MapDestroy(map_decodifica);
    huffman_tree = BinaryTreeDestroy(huffman_tree);

    return 0;
}