#include "utils.h"
#include <stdlib.h>

FILE *StdinRead(int *array, char *caminho)
{
    FILE *entrada_file = fopen(caminho, "r");

    if(!entrada_file)
    {
        printf("error opening file!\n");
        exit(1);
    }

    return entrada_file;
}

void AsciiCount(int *array, FILE *entrada_file)
{    
    char car;

    int codigo_ascii;

    while (!feof(entrada_file))
    {
        fscanf(entrada_file, "%c", &car);

        if(feof(entrada_file))
        break;

        codigo_ascii = car;
        array[codigo_ascii]++;
    }

    fclose(entrada_file);
}