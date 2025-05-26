#include "produto.h"
#include "lista.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void ImprimeOpcoes();

int main(int argc, char *argv[])
{
    char op;
    int cod;

    Lista *l = CriaLista();

    while (1)
    {
        ImprimeOpcoes();

        scanf("%*[^A-Za-z]");
        scanf("%c", &op);

        if (op == 'F')
            break;

        switch (op)
        {
        case 'C':

            printf("Digite nesse formato: [codigo; nome; valor] as infos do produto a ser cadastrado\n");
            Produto *p = LeProduto();
            InsereLista(l, p);

            break;

        case 'R':

            printf("Digite o codigo do produto a ser removido\n");

            scanf("%d", &cod);

            RetiraLista(l, cod);

            break;

        case 'I':

            ImprimeLista(l);

            break;

        default:
            break;
        }

    }

    DesalocaLista(l);

    return 0;
}

void ImprimeOpcoes()
{
    printf("Digite 'C' para cadastrar um produto\n");
    printf("Digite 'R' para remover um produto\n");
    printf("Digite 'I' para imprimir a lista de produtos\n");
    printf("Digite 'F' para encerrar o programa\n");
}