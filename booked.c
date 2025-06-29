#include <stdlib.h>

#include "booked.h"

static void Le_Arquivo_Leitores(char *caminho, Lista *readers_list);
static void Le_Arquivo_Livros(char *caminho, Lista *books_list);

struct booked
{
    Lista *leitores;
    Lista *livros;
};

static void Le_Arquivo_Leitores(char *caminho, Lista *readers_list)
{
    FILE *readers_file = OpenFile(caminho, "leitores.txt", 'r');

    int flag = 0;

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

}

static void Le_Arquivo_Livros(char *caminho, Lista *books_list)
{
    FILE *books_file = OpenFile(caminho, "livros.txt", 'r');

    int flag = 0;

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
}


tBooked *BookedConstruct(char *caminho)
{
    Lista *readers_list = ListConstruct();
    Lista *books_list = ListConstruct();

    Le_Arquivo_Leitores(caminho, readers_list);
    Le_Arquivo_Livros(caminho, books_list);

    tBooked *booked = (tBooked *)malloc(sizeof(tBooked));

    booked->livros = books_list;
    booked->leitores = readers_list;

    return booked;
}


void BookedDestroy(tBooked *booked)
{
    if (booked)
    {
        ListDestroy(booked->leitores, 1, ReaderDestroy);
        ListDestroy(booked->livros, 1, BookDestroy);
        free(booked);
    }
}

int Le_Comando(FILE *comando_file, int *vet, int flag)
{
    char linha[50];

    if (!flag)
        fgets(linha, 50, comando_file);

    while (fgets(linha, 50, comando_file) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';

        sscanf(linha, "%d;%d;%d;%d", &vet[0], &vet[1], &vet[2], &vet[3]);

        return 1;
    }

    return 0;
}


void ExecutaBooked(int *vet, FILE *stdout_file, tBooked *booked)
{
    int op = vet[0], id_r1 = vet[1], id_r2 = vet[3], id_book = vet[2];
    Leitor *reader1, *reader2;
    Livro *book;

    if (op < 1 || op > 8)
    {
        fprintf(stdout_file, "Erro: Comando %d não reconhecido\n", op);
        return;
    }

    if (id_r1 > 0)
        reader1 = ListSearch(booked->leitores, &id_r1, ReaderCompare);
    if (id_r2 > 0)
        reader2 = ListSearch(booked->leitores, &id_r2, ReaderCompare);
    if (id_book > 0)
        book = ListSearch(booked->livros, &id_book, BookCompare);

    if (op == 1 || op == 2)
    {
        if (reader1 == NULL)
        {
            fprintf(stdout_file, "Erro: Leitor com ID %d não encontrado\n", id_r1);
            return;
        }
        if (book == NULL)
        {
            fprintf(stdout_file, "Erro: Livro com ID %d não encontrado\n", id_book);
            return;
        }
    }

    if (op == 3)
    {
        if (reader1 == NULL)
        {
            fprintf(stdout_file, "Erro: Leitor recomendador com ID %d não encontrado\n", id_r1);
            return;
        }
        if (reader2 == NULL)
        {
            fprintf(stdout_file, "Erro: Leitor destinatário com ID %d não encontrado\n", id_r2);
            return;
        }
        if (book == NULL)
        {
            fprintf(stdout_file, "Erro: Livro com ID %d não encontrado\n", id_book);
            return;
        }
    }

    if (op == 4 || op == 5)
    {
        if (reader2 == NULL)
        {
            fprintf(stdout_file, "Erro: Leitor recomendador com ID %d não encontrado\n", id_r2);
            return;
        }
        if (reader1 == NULL)
        {
            fprintf(stdout_file, "Erro: Leitor com ID %d não encontrado\n", id_r1);
            return;
        }
    }

    if (op == 6 || op == 7)
    {
        if (reader1 == NULL)
        {
            fprintf(stdout_file, "Erro: Leitor com ID %d não encontrado\n", id_r1);
            return;
        }
        if (reader2 == NULL)
        {
            fprintf(stdout_file, "Erro: Leitor com ID %d não encontrado\n", id_r2);
            return;
        }
    }

    switch (op)
    {
    case 1:
        AddLidosList(reader1, book, stdout_file);
        break;
    case 2:
        AddWishList(reader1, book, stdout_file);
        break;
    case 3:
        AddRecList(reader1, reader2, book, stdout_file);
        break;
    case 4:
        AceitaRecomendacao(reader2, reader1, id_book, stdout_file);
        break;
    case 5:
        RecusaRecomendacao(reader2, reader1, id_book, stdout_file);
        break;
    case 6:
        Descobre_Livros_Em_Comum(reader1, reader2, stdout_file);
        break;
    case 7:
        GrafoSearchAfinidades(reader1, reader2, stdout_file);
        break;
    case 8:
        BookedPrint(booked, stdout_file);
        break;

    default:
        break;
    }
}

void UpdateAfinidades(tBooked *booked)
{
    Celula *cell_atual = GetFirstCell(booked->leitores);
    Celula *cell_prox;

    for (cell_atual; cell_atual != NULL; cell_atual = cell_atual->prox)
    {
        for (cell_prox = cell_atual->prox; cell_prox != NULL; cell_prox = cell_prox->prox)
        {
            UpdateAfinidades_Aux(cell_atual->data, cell_prox->data);
        }
    }
}

void BookedPrint(tBooked *booked,FILE *stdout_file)
{
    fprintf(stdout_file, "Imprime toda a BookED\n\n");
    ListPrint(booked->leitores, PrintReader, stdout_file, 0);
}





