#include "leitor.h"
#include "livro.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LIBERA_DATA 1
#define NOT_LIBERA_DATA 0

void ComandoPrint(int id_comando, void *r1, void *r2, void *b, FILE *stdout_file);

void ComandoExecute(int *vet, FILE *stdout_file, Lista *reader_list, Lista *books_list);

int Le_Comando(FILE *c_file, int *vet, int flag);

FILE *OpenFile(char *diretorio, char *filename);

void CloseFile(FILE *arq);

int main(int argc, char *argv[])
{
    int flag = 0;

    FILE *readers_file = OpenFile(argv[1], "leitores.txt");

    Lista *readers_list = ListConstruct();

    while (1)
    {
        Leitor *reader = Le_Reader(readers_file, flag);
        flag++;

        if (reader == NULL)
        {
            flag = 0; // set flag
            break;
        }

        ListPushBack(readers_list, reader);
    }

    CloseFile(readers_file);

    FILE *books_file = OpenFile(argv[1], "livros.txt");

    Lista *books_list = ListConstruct();

    while (1)
    {
        Livro *book = Le_Book(books_file, flag);
        flag++;

        if (book == NULL)
        {
            flag = 0;
            break;
        }

        ListPushBack(books_list, book);
    }

    CloseFile(books_file);

    FILE *comandos_file = OpenFile(argv[1], "comandos.txt");
    int stop;

    FILE *stdout_file = fopen("saida.txt", "w");

    int vet_comandos[4];

    while (1)
    {
        stop = Le_Comando(comandos_file, vet_comandos, flag);
        flag++;

        if (!stop)
        {
            flag = 0; // set flag
            break;
        }

        ComandoExecute(vet_comandos, stdout_file, readers_list, books_list);
    }

    CloseFile(comandos_file);
    CloseFile(stdout_file);

    ListDestroy(books_list, 1, BookDestroy);
    ListDestroy(readers_list, 1, ReaderDestroy);

    return 0;
}

FILE *OpenFile(char *diretorio, char *filename)
{
    char stream[100];

    sprintf(stream, "%s/%s", diretorio, filename);

    FILE *arq = fopen(stream, "r");

    if (!arq)
    {
        printf("Error opening %s!\n", filename);
        exit(0);
    }

    return arq;
}

void CloseFile(FILE *arq)
{
    fclose(arq);
}

int Le_Comando(FILE *c_file, int *vet, int flag)
{
    char linha[50];

    if (!flag)
        fgets(linha, 50, c_file);

    while (fgets(linha, 50, c_file) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';

        sscanf(linha, "%d;%d;%d;%d", &vet[0], &vet[1], &vet[2], &vet[3]);

        return 1;
    }

    return 0;
}

void ComandoExecute(int *vet, FILE *stdout_file, Lista *reader_list, Lista *books_list)
{
    int id_comando = vet[0], id1 = vet[1], id2 = vet[2], id3 = vet[3];

    void *reader1;
    if(id1 > 0)
    reader1 = ListSearch(reader_list, id1, ReaderCompare);

    void *book;
    if(id2 > 0)
    book = ListSearch(books_list, id2, BookCompare);

    void *reader2;
    if(id3 > 0)
    reader2 = ListSearch(reader_list, id3, ReaderCompare);

    switch (id_comando)
    {
    case 1:
        ListPushBack(GetLidosList(reader1), book);
        ComandoPrint(id_comando, reader1, reader2, book, stdout_file);
        break;
    case 2:
        ListPushBack(GetWishList(reader1), book);
        ComandoPrint(id_comando, reader1, reader2, book, stdout_file);
        break;
    case 3:
        ComandoPrint(id_comando, reader1, reader2, book, stdout_file);
        break;
    case 4:
        ListPushBack(GetRecList(reader1), book);
        ComandoPrint(id_comando, reader1, reader2, book, stdout_file);
        break;
    case 5:
        ComandoPrint(id_comando, reader1, reader2, book, stdout_file);
        break;
    case 6:
        /* code */
        break;
    case 7:
        /* code */
        break;
    case 8:
        /* code */
        break;

    default:
        break;
    }
}

void ComandoPrint(int id_comando, void *r1, void *r2, void *b, FILE *stdout_file)
{
    switch (id_comando)
    {
    case 1:
        fprintf(stdout_file, "%s leu \"%s\"\n", GetReaderName(r1), GetBookTitle(b));
        break;
    case 2:
        fprintf(stdout_file, "%s deseja ler \"%s\"\n", GetReaderName(r1), GetBookTitle(b));
        break;
    case 3:
        fprintf(stdout_file, "%s recomenda \"%s\" para %s\n", GetReaderName(r1), GetBookTitle(b), GetReaderName(r2));
        break;
    case 4:
        fprintf(stdout_file, "%s aceita recomendação \"%s\" de %s\n", GetReaderName(r1), GetBookTitle(b), GetReaderName(r2));
        break;
    case 5:
        fprintf(stdout_file, "%s rejeita recomendação \"%s\" de %s\n", GetReaderName(r1), GetBookTitle(b), GetReaderName(r2));
        break;
    case 6:
        /* code */
        break;
    case 7:
        /* code */
        break;
    case 8:
        /* code */
        break;

    default:
        break;
    }
}