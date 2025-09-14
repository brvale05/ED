/** 
 * @file descompactador.c
 * @author Bruno Vale e Davi sena
 */

#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"
#include "bitmap.h"

#define VAZIO 1

int main(int argc, char **argv)
{
    int index = 0;
    int flag_arv_unica = 0;

    FILE *input_file = fopen(argv[1], "rb");

    unsigned int tree_qtdbits = le_qtdbits(input_file);

    //Verifica se arquivo está vazio
    if(!tree_qtdbits)
    {
        fclose(input_file);
        file_reconstruct(NULL, NULL, argv[1], VAZIO);
        //encerra programa.
        exit(0);
    }

    //le o bitmap da árvore de huffman contido no arquivo compactado
    bitmap *tree_bm = bitmap_descompacta(tree_qtdbits, input_file);

    unsigned int text_qtdbits = le_qtdbits(input_file);

    //le o bitmap da informação que foi codificada contido no arquivo compactado
    bitmap *text_bm = bitmap_descompacta(text_qtdbits, input_file);

    fclose(input_file);

    //preenchendo um vetor char com a sequência de bits presente no tree_bm 
    char tree_code[tree_qtdbits];
    preenche_bits_array(tree_code, tree_qtdbits, tree_bm);

    //recria árvore de huffman
    Arv *huffman_tree = huffmanTree_descompacta(tree_code, &index, tree_qtdbits);

    //CASO ESPECIAL: árvore de único nó necessita de um cuidado a parte
    if(eh_unica_arv(huffman_tree))
    flag_arv_unica = 1;

    int tree_height = 1;
    
    if(!flag_arv_unica)
    tree_height = altura_arv(huffman_tree);

    char huff_code[tree_height];

    //vetor de ponteiros para uma estrutura do tipo 'Cod', guarda informações como: código de huffman e seu respectivo caracter
    Cod **tabela_cod = malloc(sizeof(Cod*) * 256);
    for(int i = 0; i < 256; i++)
    tabela_cod[i] = NULL;

    //reconstrói a tabela a partir da árvore de huffman descompactada
    tabelaCod_reconstruct(huffman_tree, huff_code, 0, tabela_cod, flag_arv_unica);

    //recria arquivo original
    file_reconstruct(huffman_tree, text_bm, argv[1], !VAZIO);

    bitmapLibera(tree_bm);
    bitmapLibera(text_bm);
    desaloca_vetorTabela_cod(tabela_cod);
    libera_arv(huffman_tree);

    return 0;
}