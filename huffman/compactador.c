#include <stdio.h>
#include <stdlib.h>

#include "mapacodificacao.h"
#include "pilha.h"

int main(int argc, char **argv)
{
    unsigned int array_frequencias[256] = {0};
    unsigned int qtd_bits = 0;
    unsigned int tree_size = 0;

    FrequencyCount(array_frequencias, argv[1]);

    Pilha *p = PilhaConstruct();
    PilhaPushBack(p, array_frequencias);
    OrdenaPilha(p);

    Arvore *huffman_tree = HuffmanTreeConstruct(p);
    GetTreeBitsSize(huffman_tree, 0, &tree_size);
    bitmap *tree_bitmap = bitmapInit(tree_size);

    int tree_qtdbits = TreeHeight(huffman_tree);
    char aux_array[tree_qtdbits];

    MapaCodificacao *map_codifica = MapaCodificacaoConstruct(TAM_MAX_MAPA);

    BinaryCodeConstruct(huffman_tree, aux_array, 0, map_codifica, array_frequencias, &qtd_bits);

    bitmap *text_bitmap = bitmapInit(qtd_bits);

    BitMapCompacta(map_codifica, argv[1], text_bitmap);

    CompactaHuffmanTree(huffman_tree, aux_array, 0, tree_bitmap);

    WriteFileCompactado(text_bitmap, tree_bitmap, qtd_bits, tree_size, argv[1]);

    huffman_tree = BinaryTreeDestroy(huffman_tree);
    MapDestroy(map_codifica);
    PilhaDestroy(p);
    bitmapLibera(text_bitmap);
    bitmapLibera(tree_bitmap);

    return 0;
}