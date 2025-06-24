#include "leitor.h"

struct Leitor
{
    int id;
    char *nome;
    Lista *pref_list; // lista de generos preferidos
    Lista *lidos_list;
    Lista *wish_list;
    Lista *rec_list;
    Lista *afin_list;
};

Leitor *ReaderConstruct(int id, char *nome, Lista *p_list)
{
    Leitor *l = calloc(1, sizeof(Leitor));

    l->id = id;
    l->nome = nome;
    l->pref_list = p_list;
    l->lidos_list = ListConstruct();
    l->wish_list = ListConstruct();
    l->rec_list = ListConstruct();
    l->afin_list = ListConstruct();

    return l;
}

void ReaderDestroy(void *data)
{
    if (((Leitor *)data))
    {
        if (((Leitor *)data)->nome)
        {
            free(((Leitor *)data)->nome);
        }

        ListDestroy(((Leitor *)data)->pref_list, 1, StrDestroy);
        ListDestroy(((Leitor *)data)->lidos_list, 0, BookDestroy);
        ListDestroy(((Leitor *)data)->wish_list, 0, BookDestroy);
        ListDestroy(((Leitor *)data)->rec_list, 0, BookDestroy);
        ListDestroy(((Leitor *)data)->afin_list, 0, ReaderDestroy);

        free(((Leitor *)data));
    }
}

Leitor *Le_Reader(FILE *r_file, int flag)
{
    Lista *pref_list = ListConstruct();

    int id, n_afinidades, tam;
    char linha[200];
    char *token;
    char *nome;

    if (!flag)
        fgets(linha, 200, r_file);

    while (fgets(linha, 200, r_file) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0';

        token = strtok(linha, ";");

        id = atoi(token);

        token = strtok(NULL, ";");

        tam = (strlen(token) + 1);
        nome = malloc(sizeof(char) * tam);
        strcpy(nome, token);

        token = strtok(NULL, ";");
        token = strtok(NULL, ";");

        while (token != NULL)
        {
            tam = (strlen(token) + 1);
            char *afinidade = malloc(sizeof(char) * tam);
            strcpy(afinidade, token);

            ListPushBack(pref_list, afinidade);

            token = strtok(NULL, ";");
        }

        Leitor *l = ReaderConstruct(id, nome, pref_list);

        return l;
    }

    ListDestroy(pref_list, 1, StrDestroy);

    return NULL;
}

int ReaderCompare(void *data, void *id)
{
    int *chave = (int *)id;

    if (((Leitor *)data)->id == *chave)
        return 1;

    return 0;
}

Lista *GetPrefList(Leitor *l)
{
    return l->pref_list;
}

Lista *GetLidosList(Leitor *l)
{
    return l->lidos_list;
}

Lista *GetWishList(Leitor *l)
{
    return l->wish_list;
}

Lista *GetRecList(Leitor *l)
{
    return l->rec_list;
}

char *GetReaderName(Leitor *l)
{
    return l->nome;
}

int GetReaderId(Leitor *l)
{
    return l->id;
}

void UpdateAfinidades_Aux(Leitor *l1, Leitor *l2)
{
    int id_l2 = GetReaderId(l2);

    if (ListSearch(l1->afin_list, &id_l2, ReaderCompare))
        return;

    Celula *cell_pref_l1 = GetFirstCell(l1->pref_list);

    for (cell_pref_l1; cell_pref_l1 != NULL; cell_pref_l1 = cell_pref_l1->prox)
    {
        char *genero = GetDataCell(cell_pref_l1);

        if (ListSearch(l2->pref_list, genero, StrCompare))
        {
            ListPushBack(l1->afin_list, l2);
            ListPushBack(l2->afin_list, l1);
            return;
        }
    }
}

void PrintBookTitle(Lista *books_list, FILE *stdout_file)
{
    Celula *cell = GetFirstCell(books_list);
    Livro *book;

    for (cell; cell != NULL; cell = cell->prox)
    {
        book = GetDataCell(cell);
        fprintf(stdout_file, "%s", GetBookTitle(book));

        if (cell->prox != NULL)
            fprintf(stdout_file, ", ");
    }

    fprintf(stdout_file, "\n");
}

void Descobre_Livros_Em_Comum(Leitor *l1, Leitor *l2, FILE *stdout_file)
{
    Lista *livros_em_comum = ListConstruct();
    Celula *cell_leitor1 = GetFirstCell(l1->lidos_list);
    int book_id;

    for (cell_leitor1; cell_leitor1 != NULL; cell_leitor1 = cell_leitor1->prox)
    {
        book_id = GetBookId(cell_leitor1->data);

        if (ListSearch(l2->lidos_list, &book_id, BookCompare))
        {
            ListPushBack(livros_em_comum, GetDataCell(cell_leitor1));
        }
    }

    fprintf(stdout_file, "Livros em comum entre %s e %s: ", l1->nome, l2->nome);
    cell_leitor1 = GetFirstCell(livros_em_comum);

    if (cell_leitor1 == NULL)
    {
        fprintf(stdout_file, "Nenhum livro em comum\n");
    }
    else
    {
        PrintBookTitle(livros_em_comum, stdout_file);
    }

    ListDestroy(livros_em_comum, 0, BookDestroy);
}

void GrafoSearchAfinidades(Leitor *leitor_origem, Leitor *leitor_alvo, FILE *stdout_file)
{
    Lista *visitados = ListConstruct();

    int existe_afin = GrafoSearch(leitor_origem, leitor_alvo, visitados);

    if (existe_afin)
    {
        fprintf(stdout_file, "Existe afinidade entre %s e %s\n", leitor_origem->nome, leitor_alvo->nome);
    }
    if (!existe_afin)
    {
        fprintf(stdout_file, "Não existe afinidade entre %s e %s\n", leitor_origem->nome, leitor_alvo->nome);
    }

    ListDestroy(visitados, 0, ReaderDestroy);
}

int GrafoSearch(Leitor *leitor_origem, Leitor *leitor_alvo, Lista *visitados)
{
    ListPushBack(visitados, leitor_origem);

    int id_leitor_alvo = GetReaderId(leitor_alvo);
    // procura leitor alvo na lista de afinidades do leitor origem
    Leitor *destino = ListSearch(leitor_origem->afin_list, &id_leitor_alvo, ReaderCompare);

    // Se destino != NULL = Encontrou o leitor
    if (destino)
    {
        return 1;
    }

    // Continua Busca
    Celula *cell = GetFirstCell(leitor_origem->afin_list);

    for (cell; cell != NULL; cell = cell->prox)
    {
        int id_prox_busca = GetReaderId(cell->data);

        if (!ListSearch(visitados, &id_prox_busca, ReaderCompare))
        {
            if (GrafoSearch(cell->data, leitor_alvo, visitados))
                return 1;
        }
    }

    return 0;
}

void AddLidosList(Leitor *reader, Livro *book, FILE *stdout_file)
{
    int id = GetBookId(book);

    if (ListSearch(reader->lidos_list, &id, BookCompare))
    {
        fprintf(stdout_file, "%s já leu \"%s\"\n", reader->nome, GetBookTitle(book));
        return;
    }

    ListPushBack(reader->lidos_list, book);
    fprintf(stdout_file, "%s leu \"%s\"\n", reader->nome, GetBookTitle(book));
}

void AddWishList(Leitor *reader, Livro *book, FILE *stdout_file)
{
    int id = GetBookId(book);

    if (ListSearch(reader->wish_list, &id, BookCompare))
    {
        fprintf(stdout_file, "%s já deseja ler \"%s\"\n", reader->nome, GetBookTitle(book));
        return;
    }

    ListPushBack(reader->wish_list, book);
    fprintf(stdout_file, "%s deseja ler \"%s\"\n", reader->nome, GetBookTitle(book));
}

void AddRecList(Leitor *reader_inicial, Leitor *reader_destino, Livro *book, FILE *stdout_file)
{
    int id = GetBookId(book);

    if (GetReaderId(reader_inicial) == GetReaderId(reader_destino))
    {
        fprintf(stdout_file, "%s não pode recomendar livros para si mesmo\n", reader_destino->nome);
        return;
    }

    if (ListSearch(reader_destino->wish_list, &id, BookCompare))
    {
        fprintf(stdout_file, "%s já deseja ler \"%s\", recomendação desnecessária\n", reader_destino->nome, GetBookTitle(book));
        return;
    }

    if (ListSearch(reader_destino->lidos_list, &id, BookCompare) != NULL)
    {
        fprintf(stdout_file, "%s não precisa da recomendação de \"%s\" pois já leu este livro\n", reader_destino->nome, GetBookTitle(book));
        return;
    }

    ListPushBack(reader_destino->rec_list, book);
    fprintf(stdout_file, "%s recomenda \"%s\" para %s\n", reader_inicial->nome, GetBookTitle(book), reader_destino->nome);
}

void AceitaRecomendacao(Leitor *reader_origem, Leitor *reader_destino, int id, FILE *stdout_file)
{
    Livro *book = ListRemove(reader_destino->rec_list, BookCompare, &id);

    if (book == NULL)
    {
        fprintf(stdout_file, "%s não possui recomendação do livro ID %d feita por %s\n", reader_destino->nome, id, reader_origem->nome);
        return;
    }

    ListPushBack(reader_destino->wish_list, book);
    fprintf(stdout_file, "%s aceita recomendação \"%s\" de %s\n", reader_destino->nome, GetBookTitle(book), reader_origem->nome);
}

void RecusaRecomendacao(Leitor *reader_origem, Leitor *reader_destino, int id, FILE *stdout_file)
{
    Livro *book = ListRemove(reader_destino->rec_list, BookCompare, &id);

    if (book == NULL)
    {
        fprintf(stdout_file, "%s não possui recomendação do livro ID %d feita por %s\n", reader_destino->nome, id, reader_origem->nome);
        return;
    }

    fprintf(stdout_file, "%s rejeita recomendação \"%s\" de %s\n", reader_destino->nome, GetBookTitle(book), reader_origem->nome);
}
