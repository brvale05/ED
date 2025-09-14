/**
 * @file codificacao.h
 * @brief Arquivo de cabeçalho para as funções de codificação de Huffman.
 * @author Bruno Vale e Davi sena
 * Este arquivo declara as estruturas e protótipos de funções necessárias
 * para gerar, manipular e acessar a tabela de códigos de Huffman, que
 * mapeia cada caractere a uma sequência de bits única.
 */

#ifndef COD 
#define COD 

// Inclui os cabeçalhos das estruturas de dados de Árvore e Lista de Árvores,
// que são necessárias para construir a árvore de Huffman.
#include "listaArvores.h"
#include "arvore.h"

/**
 * @brief Declaração avançada (forward declaration) da estrutura Cod.
 * Isso permite o uso de ponteiros para 'Cod' (como 'Cod*') sem precisar
 * da definição completa da estrutura, ajudando a evitar dependências circulares.
 * A definição completa da struct está no arquivo .c.
 */
typedef struct Cod Cod;

/**
 * @brief Inicializa a tabela de codificação.
 * Preenche a tabela com valores padrão ou nulos antes de ser populada.
 * @param tabela_cod Um ponteiro para a tabela (vetor de ponteiros para Cod) a ser inicializada.
 */
void inicializa_vetor_COD(Cod **tabela_cod);

/**
 * @brief Aloca memória para a tabela de codificação.
 * Cria um vetor de ponteiros para 'Cod' com o tamanho especificado.
 * @param tamanho O número de entradas na tabela (geralmente 256, para a tabela ASCII).
 * @return Um ponteiro para a tabela recém-alocada.
 */
Cod **vetor_codificacao(int tamanho);

/**
 * @brief Gera os códigos de Huffman recursivamente.
 * Percorre a árvore de Huffman para construir o código binário (string de '0's e '1's) para cada caractere (folha da árvore).
 * @param a Ponteiro para o nó atual na árvore de Huffman.
 * @param codigo String temporária usada para construir o código binário durante a recursão.
 * @param profundidade O nível atual na árvore, que corresponde ao comprimento do código.
 * @param tabela A tabela onde os códigos gerados serão armazenados.
 */
void gera_codigo(Arv *a, char *codigo, int eh_unicaArvore, int profundidade, Cod** tabela);

/**
 * @brief Conta a quantidade de bits no código de Huffman para um caractere específico.
 * @param tabela_cod A tabela de codificação.
 * @param car O caractere cujo código será medido.
 * @return O número de bits (comprimento da string do código) para o caractere.
 */
int conta_qntd_bits_HUFF(Cod **tabela_cod, unsigned char car);

/**
 * @brief Imprime a tabela de codificação de Huffman na tela.
 * Útil para depuração e para visualizar os códigos gerados.
 * @param tabela A tabela de codificação a ser impressa.
 * @param num_chars O número de caracteres na tabela a serem verificados.
 */
void imprime_tabela(Cod** tabela, int num_chars);

/**
 * @brief Retorna a string do código de Huffman para um caractere.
 * @param tabela_cod A tabela de codificação.
 * @param n O valor ASCII do caractere desejado.
 * @return Um ponteiro para a string que representa o código de Huffman.
 */
char *retorna_codigo_tabelaCOD(Cod **tabela_cod, int n);

/**
 * @brief Libera a memória alocada para a tabela de codificação.
 * Percorre a tabela e libera a memória de cada código e de cada estrutura 'Cod',
 * além de liberar a memória do próprio vetor.
 * @param tabela_cod A tabela a ser desalocada.
 */
void desaloca_vetorTabela_cod(Cod** tabela_cod);

/**
 * @brief Cria e inicializa uma nova estrutura Cod.
 * Função auxiliar para alocar e preencher uma nova entrada na tabela de codificação com o código, tamanho e caractere correspondentes.
 * @param codigo A string que representa o código binário.
 * @param tam O tamanho do código.
 * @param car O caractere associado a este código.
 * @return Ponteiro para a nova estrutura Cod criada.
 */
Cod *cod_construct(char *codigo, int tam, unsigned char car);

/**
 * @brief Reconstrói a tabela de códigos de Huffman a partir da árvore.
 * Similar à função 'gera_codigo', ela é usada no processo de descompactação para preencher a tabela de códigos novamente, mas a partir da árvore já reconstruída.
 * @param raiz Ponteiro para a raiz da árvore de Huffman.
 * @param codigo String temporária para construir o código binário.
 * @param id_profundidade Nível atual na árvore.
 * @param tabela_cod Tabela onde os códigos serão armazenados.
 * @param unica_arv Flag que indica se a árvore é única.
 */
void tabelaCod_reconstruct(Arv *raiz, char *codigo, int id_profundidade, Cod **tabela_cod, int unica_arv);

#endif 