#ifndef LEITOR_H
#define LEITOR_H

#include "lista.h"
#include "livro.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Leitor Leitor;

Leitor *ReaderConstruct(int id, char *nome, Lista *p_list);

void ReaderDestroy(void *data);

Leitor *Le_Reader(FILE *r_file, int flag);

int ReaderCompare(void *data, void *id);

void PrintReader(void *data, FILE *stdout_f);

Lista *GetPrefList(Leitor *l);

Lista *GetLidosList(Leitor *l);

Lista *GetWishList(Leitor *l);

Lista *GetRecList(Leitor *l);

char *GetReaderName(Leitor *l);

int GetReaderId(Leitor *l);

void UpdateAfinidades_Aux(Leitor *l1, Leitor *l2);

void Imprime_Livros_Em_Comum(Lista *books_list, FILE *stdout_file);

void Descobre_Livros_Em_Comum(Leitor *l1, Leitor *l2, FILE *stdout_file);

void GrafoSearchAfinidades(Leitor *leitor_origem, Leitor *leitor_alvo, FILE *stdout_file);

int GrafoSearch(Leitor *leitor_origem, Leitor *leitor_alvo, Lista *visitados);

void AddLidosList(Leitor *reader, Livro *book, FILE *stdout_file);

void AddWishList(Leitor *reader, Livro *book, FILE *stdout_file);

void AddRecList(Leitor *reader_inicial, Leitor *reader_destino, Livro *book, FILE *stdout_file);

void AceitaRecomendacao(Leitor *reader_origem, Leitor *reader_destino, int id, FILE *stdout_file);

void RecusaRecomendacao(Leitor *reader_origem, Leitor *reader_destino, int id, FILE *stdout_file);


#endif