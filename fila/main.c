#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main()
{
    Fila *fila = FilaConstruct();

    FilaPushBack(fila, 1);
    FilaPushBack(fila, 2);
    FilaPushBack(fila, 3);
    FilaPushBack(fila, 4);
    FilaPushBack(fila, 5);
    
    FilaRemove(fila);
    FilaRemove(fila);

    FilaPrint(fila);

    FilaDestroy(fila);

    return 0;
}