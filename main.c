#include "leitor.h"
#include "livro.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *OpenFile(char *diretorio, char *filename);

void CloseFile(FILE *arq);

int main(int argc, char *argv[])
{
    int flag = 0;

    FILE *readers_file = OpenFile(argv[1], "leitores.txt");

    Lista *readers_list = ListConstruct();

    while(1)
    {
        Leitor *reader = Le_Reader(readers_file, flag);
        flag++;

        if(reader == NULL)
        {
            flag = 0; //set flag
            break;
        }

        ListPushBack(readers_list, reader);
    }

    //ListPrint(readers_list, ReaderPrint);
    ListDestroy(readers_list, ReaderDestroy);

    CloseFile(readers_file);

    FILE *books_file = OpenFile(argv[1], "livros.txt");

    Lista *books_list = ListConstruct();

    while (1)
    {
        Livro *book = Le_Book(books_file, flag);
        flag++;

        if(book == NULL)
        {
            flag = 0;
            break;
        }

        ListPushBack(books_list, book);
    }
    
    //ListPrint(books_list, BookPrint);
    ListDestroy(books_list, BookDestroy);

    CloseFile(books_file);

    return 0;
}

FILE *OpenFile(char *diretorio, char *filename)
{
    char stream[100];

    sprintf(stream, "%s/%s", diretorio, filename);

    FILE *arq = fopen(stream, "r");

    if(!arq)
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