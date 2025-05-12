#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supermercado.h"
#include "filial.h"
#include "estoque.h"
#include "item.h"
#include "produto.h"

void ImprimeOpcoes();

int main(int argc, char **argv)
{
    char op;
    char nome[50];

    Supermercado *s = NULL;
    Estoque *e = NULL;
    Filial *f = NULL;
    Produto *p = NULL;
    Item *it = NULL;

    while (1)
    {
        ImprimeOpcoes();
        
        scanf("%c", &op);
        scanf("%*[^\n]");
        scanf("%*c");

        if (op == 'E')
            break;

        switch (op)
        {
        case 'S':
            printf("Digite o nome do supermercado:\n");
            //scanf("%*[^A-Za-z]");
            scanf("%[^\n]", nome);
            scanf("%*c");

            s = CriaSupermercado(nome);

            break;
        case 'F':
            printf("Digite o nome da filial:\n");

            f = LeFilial();

            e = CriaEstoque();

            printf("Digite a quantidade de itens que deseja cadastrar:\n");

            int n;
            scanf("%d", &n);

            printf("Digite as informacoes dos itens em cada linha:\n");

            for (int i = 0; i < n; i++)
            {
                p = LeProduto();

                int tam;

                scanf("%*[^0-9]");
                scanf("%d", &tam);

                it = CriaItem(tam, p);

                AtribuiItemEstoque(e, it);
            }

            AtribuiEstoque(f, e);
            AtribuiFilial(s, f);
            break;

        case 'I':
            ImprimeSupermercado(s);

        default:
            break;
        }
    }

    LiberaSupermercado(s);

    return 0;
}

void ImprimeOpcoes()
{
    printf("Escolha sua opcao:\n");
    printf("Digite 'S' para cadastrar um supermercado.\n");
    printf("Digite 'F' para cadastrar uma filial.\n");
    printf("Digite 'I' para imprimir todas as informacoes do mercado.\n");
    printf("Digite 'E' para encerrar cadastro.\n");
}