/** 
 * @file compactador.c
 * @author Bruno Vale e Davi sena
 */

#include <stdio.h>
#include <stdlib.h>

#include "listaArvores.h"
#include "codificacao.h"
#include "bitmap.h"

int main(int argc, char **argv)
{

    FILE *input_file = fopen(argv[1], "rb");

    // Verifica se o arquivo foi aberto com sucesso.
    if (!input_file)
    {
        printf("ERRO : não foi possivel abrir o arquivo de entrada\n");
        exit(0); // Encerra o programa se houver erro.
    }

    //Etapa que verifica se o arquivo está vazio.
    int file_size;
    // Move o ponteiro para o final do arquivo
    fseek(input_file, 0, SEEK_END);
    // Obtém a posição atual do ponteiro, que é o tamanho do arquivo
    file_size = ftell(input_file);

    //Se for 0, significa que o arquivo está vazio.
    if(!file_size)
    {
        fclose(input_file);

        escreve_arquivo_Compactado(NULL, 0, NULL, 0, argv[1]);
        //encerra programa.
        exit(0);
    }

    fclose(input_file);

    // Vetor para contar a frequência de cada caractere ASCII (0-255).
    int vetorAscii[256] = {0}; // elementos no vetor zerado

    //CASO ESPECIAL: CARACTER/BYTE UNICO
    //1 se existe apenas um unico caracter/byte, 0 para o contrario
    int flag_arv_unica = 0;

    // Declaração de um ponteiro para a lista que armazenará as árvores.
    Lista *lista_Arvs; // lista de arvores

    // Aloca e inicializa a lista de árvores.
    lista_Arvs = criaLista();

    // Ponteiro que armazenará a raiz da árvore de Huffman final, após todas as junções.
    Arv *Arv_principal; // vai guardar a arvore principal (arvores depois de serem juntas numa só)

    // --- ETAPA 1: CONTAGEM DE FREQUÊNCIA E CRIAÇÃO DOS NÓS FOLHA ---

    // Abre o arquivo "entrada.txt" em modo de leitura ("rb").
    input_file = fopen(argv[1], "rb");

    // Verifica se o arquivo foi aberto com sucesso.
    if (!input_file)
    {
        printf("ERRO : não foi possivel abrir o arquivo de entrada\n");
        exit(0); // Encerra o programa se houver erro.
    }

    // Variáveis para ler o caractere e armazenar seu valor ASCII.
    unsigned char car;
    int valorAscii = 0;

    // Lê o arquivo caractere por caractere.
    while (fread(&car, sizeof(unsigned char), 1, input_file) == 1)
    {
        // Obtém o valor ASCII do caractere.
        valorAscii = car;
        // Incrementa a contagem para esse caractere no vetor de frequências.
        vetorAscii[valorAscii]++;
    }

    // Fecha o arquivo após a leitura.
    fclose(input_file);

    // Itera sobre o vetor de frequências.
    for (int i = 0; i < 256; i++)
    {

        // Se um caractere apareceu no texto (frequência > 0)...
        if (vetorAscii[i] > 0)
        {

            // ...cria uma nova árvore (nó folha) vazia.
            Arv *arvore = criaArv_vazia();

            // Insere os dados do caractere (valor ASCII e frequência) no nó.
            arvore = insere_Arv(arvore, i, vetorAscii[i], EH_FOLHA);

            // Insere a nova árvore (nó folha) na lista, que a mantém ordenada por frequência.
            insereNaLista(arvore, lista_Arvs);
        }
    }

    if(unico_elem_lista(lista_Arvs))
    {
        flag_arv_unica = 1;
    }

    // --- ETAPA 2: CONSTRUÇÃO DA ÁRVORE DE HUFFMAN ---
    // Junta as duas árvores de menor frequência repetidamente, até que reste apenas uma.
    juncao_arvs_lista(lista_Arvs, flag_arv_unica);

    // A única árvore restante na lista é a árvore de Huffman completa.
    Arv_principal = retorna_Prim_arv(lista_Arvs);

    // --- ETAPA 3: GERAÇÃO DA TABELA DE CODIFICAÇÃO ---
    // Variável para armazenar a altura da árvore.
    int tree_height = 1;

    // Calcula a altura da árvore para determinar o tamanho máximo de um código.
    if(!flag_arv_unica)
    tree_height = altura_arv(Arv_principal);

    // Cria uma string (buffer) para gerar os códigos. O +1 é para o caractere nulo '\0'.
    char codigo[tree_height + 1]; // as strings possuem '\0' no final

    // Aloca a tabela que armazenará os códigos de Huffman para cada caractere.
    Cod **tabela_cod = vetor_codificacao(256);

    // Inicializa a tabela de codificação com valores padrão.
    inicializa_vetor_COD(tabela_cod);

    // Percorre a árvore de Huffman para gerar e armazenar os códigos na tabela.
    gera_codigo(Arv_principal, codigo, flag_arv_unica, 0, tabela_cod);

    // --- ETAPA 4: CÁLCULO DO TAMANHO TOTAL EM BITS E CODIFICAÇÃO ---
    // Variável para somar o número total de bits do arquivo codificado.
    unsigned int totalBits_text = 0;

    unsigned int totalBits_arv = 0;

    bits_arv(Arv_principal, &totalBits_arv);

    // Reabre o arquivo de entrada para ler seu conteúdo novamente.
    input_file = fopen(argv[1], "rb");

    if (!input_file)
    {
        printf("ERRO : não foi possivel abrir o arquivo de entrada\n");
        exit(0); // Encerra o programa se houver erro.
    }

    // Para cada caractere no arquivo...
    while (fread(&car, sizeof(char), 1, input_file) == 1)
    {

        // ...soma a quantidade de bits do seu respectivo código de Huffman.
        totalBits_text += conta_qntd_bits_HUFF(tabela_cod, car);
    }

    // Fecha o arquivo.
    fclose(input_file);

    // --- ETAPA 5: PREENCHIMENTO DOS BITMAPs ---
    // Inicializa o bitmap com o tamanho exato calculado.
    bitmap *bm_text = bitmapInit(totalBits_text);
    bitmap *bm_arvore = bitmapInit(totalBits_arv);

    coloca_arvore_bitmap(Arv_principal, bm_arvore);

    // Reabre o arquivo de entrada uma última vez para a codificação final.
    input_file = fopen(argv[1], "rb");

    if (!input_file)
    {
        printf("ERRO : não foi possivel abrir o arquivo de entrada\n");
        exit(0); // Encerra o programa se houver erro.
    }

    // Para cada caractere no arquivo...
    while (fread(&car, sizeof(char), 1, input_file) == 1)
    {
        // ...preenche o bitmap com a sequência de bits correspondente ao caractere.
        bitmap_preenche(bm_text, tabela_cod, car);
    }

    // Fecha o arquivo.
    fclose(input_file);

    escreve_arquivo_Compactado(bm_text, totalBits_text, bm_arvore, totalBits_arv, argv[1]);

    // Libera a memória alocada para a lista e suas árvores.
    desalocaLista(lista_Arvs);

    // Libera a memória alocada para a tabela de codificação.
    desaloca_vetorTabela_cod(tabela_cod);

    // Libera a memória alocada para o bitmap.
    bitmapLibera(bm_text);

    bitmapLibera(bm_arvore);

    return 0;
}