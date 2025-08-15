#ifndef MAPA_DE_CODIFICACAO
#define MAPA_DE_CODIFICACAO

#define TAM_MAX_MAPA 256 // Máximo de caracteres ASCII

#include "codigohuffman.h"
#include "arvore.h"
#include "bitmap.h"
#include "utils.h"

// Definição opaca da estrutura MapaCodificacao
typedef struct MapaCodificacao MapaCodificacao;

/**
 * Cria um mapa de codificação.
 * @param tam Número máximo de elementos no mapa.
 * @return Ponteiro para o mapa criado.
 */
MapaCodificacao *MapaCodificacaoConstruct(int tam);

/**
 * Adiciona um código Huffman ao mapa.
 * @param map       Ponteiro para o mapa.
 * @param item_map  Ponteiro para o código Huffman do caractere.
 * @param id        Índice (valor ASCII do caractere).
 */
void MapPushBack(MapaCodificacao *map, CodigoHuffman *item_map, unsigned int id);

/**
 * Libera toda a memória usada pelo mapa.
 * @param map Ponteiro para o mapa.
 */
void MapDestroy(MapaCodificacao *map);

/**
 * Constrói o código binário de cada caractere percorrendo a árvore de Huffman.
 * @param raiz               Ponteiro para a árvore.
 * @param codigo             Vetor temporário com o código atual.
 * @param id_profundidade    Profundidade atual na árvore.
 * @param map                Ponteiro para o mapa de codificação.
 * @param array_de_frequencias Vetor com as frequências dos caracteres.
 * @param qtd_bits           Ponteiro para o total de bits do arquivo codificado.
 */
void BinaryCodeConstruct(Arvore *raiz, char *codigo, int id_profundidade,
                         MapaCodificacao *map, unsigned int *array_de_frequencias,
                         unsigned int *qtd_bits);

/**
 * Abre o arquivo de entrada para leitura e compacta os dados do mapa em um bitmap para salvar no arquivo posteriormente.
 * @param codifica_map   Mapa de codificação.
 * @param caminho        Caminho do arquivo original.
 * @param map            Ponteiro para bitmap atualizado.
 */
void BitMapCompacta(MapaCodificacao *codifica_map, char *caminho, bitmap *map);

/**
 * Reconstrói o mapa de codificação a partir da árvore que foi descompactada.
 * @param raiz            Ponteiro para a árvore.
 * @param codigo          Código binário temporário.
 * @param id_profundidade Profundidade atual.
 * @param map             Ponteiro para o mapa.
 */
void BinaryCodeDescompacta(Arvore *raiz, char *codigo, int id_profundidade, MapaCodificacao *map);

/**
 * Reconstrói o arquivo original a partir da árvore e dos bits codificados no bitmap.
 * @param raiz    Ponteiro para a árvore de Huffman.
 * @param bm      Ponteiro para o bitmap com os dados compactados.
 * @param caminho Caminho para o arquivo de saída.
 */
void OriginalFileReconstruct(Arvore *raiz, bitmap *bm, char *caminho);

/**
 * Função auxiliar recursiva para reconstruir o arquivo original.
 * @param raiz        Ponteiro para a árvore.
 * @param flag        Ponteiro para variável que reinicia a busca na árvore.
 * @param output_file Ponteiro para o arquivo de saída.
 */
void OriginalFileReconstruct_Aux(Arvore *raiz, int *flag, FILE *output_file);

#endif
