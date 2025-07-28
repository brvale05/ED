#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "pilha.h"

int main(int argc, char **argv)
{
    int ascii[128] = {0};

    AsciiCount(ascii, StdinRead(ascii, argv[1]));
    
    Pilha *p = PilhaConstruct();
    PilhaVectorUpdate(p, ascii);
    OrdenaPilha(p);

    Arvore *binary_tree = BinaryTreeConstruct(p);
    BinaryTreePrint(binary_tree);

    printf("%d", TreeHeight(binary_tree));

    binary_tree = BinaryTreeDestroy(binary_tree);
    PilhaDestroy(p);

    return 0;
}