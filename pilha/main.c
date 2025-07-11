#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

int main()
{
    Pilha *pilha = PilhaConstruct();

    PilhaRemove1(pilha);

    PilhaPush1(pilha, 1);
    PilhaPush1(pilha, 2);
    PilhaPush1(pilha, 3);
    PilhaRemove1(pilha);

    PilhaRemove2(pilha);

    PilhaPush2(pilha, 10);
    PilhaPush2(pilha, 11);
    PilhaPush2(pilha, 12);
    PilhaRemove2(pilha);

    PilhaPrint(pilha);

    PilhaDestroy(pilha);

    return 0;
}