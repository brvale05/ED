/** Define um TAD representando um mapa de bits.
 * @file bitmap.c
 * @author Joao Paulo Andrade Almeida (jpalmeida@inf.ufes.br)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitmap.h"

struct map
{
	unsigned int max_size;	 ///< tamanho maximo em bits
	unsigned int length;	 ///< tamanho atual em bits
	unsigned char *contents; ///< conteudo do mapa de bits
};

/**
 * Funcao auxiliar que imprime uma mensagem de falha e aborta o programa caso testresult seja falso.
 * @param testresult Valor booleano representando o resultado do teste que deveria ser verdadeiro.
 * @param message A mensagem para ser impressa se resultado do teste for falso.
 */
void assert(int testresult, char *message)
{
	if (!testresult)
	{
		printf("%s\n", message);
		exit(EXIT_FAILURE);
	}
}

/**
 * Retorna o conteudo do mapa de bits.
 * @param bm O mapa de bits.
 */
unsigned char *bitmapGetContents(bitmap *bm)
{
	return bm->contents;
}

/**
 * Retorna o tamanho maximo do mapa de bits.
 * @param bm O mapa de bits.
 * @return O tamanho maximo do mapa de bits.
 */
unsigned int bitmapGetMaxSize(bitmap *bm)
{
	return bm->max_size;
}

/**
 * Retorna o tamanho atual do mapa de bits.
 * @param bm O mapa de bits.
 * @return O tamanho atual do mapa de bits.
 */
unsigned int bitmapGetLength(bitmap *bm)
{
	return bm->length;
}

/**
 * Constroi um novo mapa de bits, definindo um tamanho maximo.
 * @param max_size O tamanho maximo para o mapa de bits.
 * @return O mapa de bits inicializado.
 */
bitmap *bitmapInit(unsigned int max_size)
{
	bitmap *bm;
	bm = (bitmap *)malloc(sizeof(bitmap));
	// definir tamanho maximo em bytes, com arredondamento para cima
	unsigned int max_sizeInBytes = (max_size + 7) / 8;
	// alocar espaco de memoria para o tamanho maximo em bytes
	bm->contents = calloc(max_sizeInBytes, sizeof(char));
	// verificar alocacao de memoria
	assert(bm->contents != NULL, "Erro de alocacao de memoria.");
	// definir valores iniciais para tamanho maximo e tamanho atual
	bm->max_size = max_size;
	bm->length = 0;
	return bm;
}

/**
 * Retorna o valor do bit na posicao index.
 * @param bm O mapa de bits.
 * @param index A posicao do bit.
 * @pre index<bitmapGetLength(bm)
 * @return O valor do bit.
 */
unsigned char bitmapGetBit(bitmap *bm, unsigned int index) // index in bits
{
	// verificar se index<bm.length, pois caso contrario, index e' invalido
	assert(index < bm->length, "Acesso a posicao inexistente no mapa de bits.");
	// index/8 e' o indice do byte que contem o bit em questao
	// 7-(index%8) e' o deslocamento do bit em questao no byte
	return (bm->contents[index / 8] >> (7 - (index % 8))) & 0x01;
}

/**
 * Modifica o valor do bit na posicao index.
 * @param bm O mapa de bits.
 * @param index A posicao do bit.
 * @param bit O novo valor do bit.
 * @post bitmapGetBit(bm,index)==bit
 */
static void bitmapSetBit(bitmap *bm, unsigned int index, unsigned char bit)
{
	// verificar se index<bm->length, pois caso contrario, index e' invalido
	assert(index < bm->length, "Acesso a posicao inexistente no mapa de bits.");
	// index/8 e' o indice do byte que contem o bit em questao
	// 7-(index%8) e' o deslocamento do bit em questao no byte
	bit = bit & 0x01;
	bit = bit << (7 - (index % 8));
	bm->contents[index / 8] = bm->contents[index / 8] | bit;
}

/**
 * Adiciona um bit no final do mapa de bits.
 * @param bm O mapa de bits.
 * @param bit O novo valor do bit.
 * @pre bitmapGetLength(bm) < bitmapGetMaxSize(bm)
 * @post (bitmapGetBit(bm,bitmapGetLength(bm) @ pre)==bit)
 * and (bitmapGetLength(bm) == bitmapGetLength(bm) @ pre+1)
 */
void bitmapAppendLeastSignificantBit(bitmap *bm, unsigned char bit)
{
	// verificar se bm->length<bm->max_size, caso contrario, o bitmap esta' cheio
	assert(bm->length < bm->max_size, "Tamanho maximo excedido no mapa de bits.");
	// como um bit sera' adicionado, devemos incrementar o tamanho do mapa de bits
	bm->length++;
	bitmapSetBit(bm, bm->length - 1, bit);
}

void bitmap_preenche(bitmap *bm, Cod **tabela_cod, unsigned char car)
{

	int ascii = 0;
	char *codigo;

	ascii = car;

	codigo = strdup(retorna_codigo_tabelaCOD(tabela_cod, ascii));

	for (int i = 0; codigo[i] != '\0'; i++)
	{
		unsigned char aux_c = codigo[i];
		bitmapAppendLeastSignificantBit(bm, aux_c);
	}

	free(codigo);
}

void coloca_arvore_bitmap(Arv *a, bitmap *bm)
{

	if (folha_arv(a))
	{

		bitmapAppendLeastSignificantBit(bm, '1'); // nó encontrado é uma folha, logo é necessario salvar os bist do char

		unsigned char c = char_arv(a);

		for (int i = 7; i >= 0; i--)
		{

			int bit = (c >> i) & 1;

			if (bit)
			{
				bitmapAppendLeastSignificantBit(bm, '1');
			}
			else
			{
				bitmapAppendLeastSignificantBit(bm, '0');
			}
		}

		return;
	}

	if (a)
	{
		// faz com os filhos do nó
		bitmapAppendLeastSignificantBit(bm, '0'); // nó nao é uma folha, logo passa pro proximo nó
		coloca_arvore_bitmap(esqueda_arv(a), bm);

		bitmapAppendLeastSignificantBit(bm, '0'); // nó nao é uma folha, logo passa pro proximo nó
		coloca_arvore_bitmap(direita_arv(a), bm);
	}

	return;
}

/**
 * Libera a memória dinâmica alocada para o mapa de bits.
 * @param bm O mapa de bits.
 */
void bitmapLibera(bitmap *bm)
{

	free(bm->contents);
	free(bm);
}

void escreve_arquivo_Compactado(bitmap *bm, unsigned int qntdbits, bitmap *arv_bm, unsigned int arv_bits, char *caminho)
{

	FILE *input_file;

	strcat(caminho, ".comp");
	input_file = fopen(caminho, "wb");

	if (!arv_bits)
	{
		fwrite(&arv_bits, sizeof(unsigned int), 1, input_file);
		fclose(input_file);
		return;
	}

	fwrite(&arv_bits, sizeof(unsigned int), 1, input_file);
	fwrite(bitmapGetContents(arv_bm), sizeof(char), (bitmapGetMaxSize(arv_bm) + 7) / 8, input_file);

	fwrite(&qntdbits, sizeof(unsigned int), 1, input_file);
	fwrite(bitmapGetContents(bm), sizeof(char), (bitmapGetMaxSize(bm) + 7) / 8, input_file);

	fclose(input_file);
}

unsigned int le_qtdbits(FILE *input_file)
{
	unsigned int qtdbits;
	fread(&qtdbits, sizeof(unsigned int), 1, input_file);

	return qtdbits;
}

bitmap *bitmap_descompacta(unsigned int max_size, FILE *input_file)
{
	bitmap *bm;
	bm = (bitmap *)malloc(sizeof(bitmap));

	bm->contents = calloc((max_size + 7) / 8, sizeof(char));

	fread(bm->contents, sizeof(char), (max_size + 7) / 8, input_file);

	// definir valores iniciais para tamanho maximo e tamanho atual
	bm->max_size = max_size;
	bm->length = max_size;

	return bm;
}

void preenche_bits_array(char *array_bits, int tam, bitmap *tree_bm)
{
	for (int i = 0; i < tam; i++)
	{
		unsigned char car;
		car = bitmapGetBit(tree_bm, i);

		if (car)
		{
			array_bits[i] = '1';
		}
		else
		{
			array_bits[i] = '0';
		}
	}
}

void file_reconstruct_aux(Arv *raiz, int *flag, FILE *output_file)
{
	if (folha_arv(raiz))
	{
		unsigned char c = char_arv(raiz);

		fwrite(&c, sizeof(char), 1, output_file);
		*flag = *flag + 1;
	}
}

void file_reconstruct(Arv *raiz, bitmap *bm, char *caminho, int arq_vazio)
{
	char *posicao;

	// retira o ".comp" do caminho passado para recriar arquivo original.
	posicao = strstr(caminho, ".comp");
	posicao[0] = '\0';

	FILE *output_file = fopen(caminho, "wb");

	if(arq_vazio)
	{
		fclose(output_file);
		return;
	}

	Arv *arv_aux = raiz;

	int flag = 0;

	for (int i = 0; i < bitmapGetLength(bm); i++)
	{
		unsigned char car;
		car = bitmapGetBit(bm, i);

		if (eh_unica_arv(raiz))
		{
			file_reconstruct_aux(arv_aux, &flag, output_file);
		}
		else
		{
			if (car)
			{
				arv_aux = direita_arv(arv_aux);
				file_reconstruct_aux(arv_aux, &flag, output_file);
			}
			else
			{
				arv_aux = esqueda_arv(arv_aux);
				file_reconstruct_aux(arv_aux, &flag, output_file);
			}
		}

		if (flag)
		{
			arv_aux = raiz;
			flag = 0;
		}
	}

	fclose(output_file);
}