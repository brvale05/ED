#include "utils.h"

FILE *OpenFile(char *diretorio, char *filename, char modo)
{
    char stream[100];
     FILE *arq;

    if (modo == 'r')
    {
        sprintf(stream, "%s/%s", diretorio, filename);

        arq = fopen(stream, "r");
    }
    else
    {
        arq = fopen(filename, "w");
    }

    if (!arq)
    {
        printf("Error opening %s!\n", filename);
        exit(0);
    }

    return arq;
}

void CloseFile(FILE *f)
{
    fclose(f);
}