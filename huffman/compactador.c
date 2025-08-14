// #include <stdio.h>
// #include <stdlib.h>

// #include "utils.h"
// #include "pilha.h"
// #include "arvore.h"
// #include "table.h"

// int main(int argc, char **argv)
// {
//     unsigned int ascii[256] = {0};
//     unsigned int qtd_bits = 0;
//     FILE *arquivo_entrada;

//     //le o arquivo de entrada e conta a frequencia de cada caracter ou byte
//     FrequencyCount(ascii, argv[1]);
    
//     Pilha *p = PilhaConstruct();

//     //para cada caracter, cria uma arvore contendo esse caracter
//     PilhaVectorUpdate(p, ascii);
//     OrdenaPilha(p);

//     //cria arvore de huffman
//     Arvore *binary_tree = BinaryTreeConstruct(p);
//     // BinaryTreePrint(binary_tree);

//     int size = TreeHeight(binary_tree);

//     char aux_code[size];

//     //cria um vetor de tabelas contendo cada caracter
//     Tabela **tabela_codificada = TableVectorConstruct(TAM_MAX);
//     //atualiza o vetor e gera o codigo binario compactado de cada folha da arvore
//     BinaryCodeConstruct(binary_tree, aux_code, 0, tabela_codificada, ascii, &qtd_bits);

//     bitmap *mapa_de_bits = bitmapInit(qtd_bits);
//     //gera o codigo binario final a ser escrito no arquivo compactado
//     UpdateMapaDeBits(tabela_codificada, argv[1], mapa_de_bits);

//     unsigned int tree_size = 0;
//     //descobre o tamanho em bits da arvore de huffman
//     GetTreeBitsSize(binary_tree, 0, &tree_size);

//     //inicializa mapa de bit da arvore de huffman
//     bitmap *tree_bitmap = bitmapInit(tree_size);

//     //gera o codigo binario da arvore
//     CompactaHuffmanTree(binary_tree, aux_code, 0, tree_bitmap);

//     //cria arquivo binario compactado
//     BinaryFileWrite(mapa_de_bits, tree_bitmap, qtd_bits, tree_size, argv[1]);

//     binary_tree = BinaryTreeDestroy(binary_tree);
//     TableVectorDestroy(tabela_codificada);
//     PilhaDestroy(p);
//     bitmapLibera(mapa_de_bits);
//     bitmapLibera(tree_bitmap);

//     return 0;
// }