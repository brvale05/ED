#include "utils.h"
#include <string.h>
#include <stdlib.h>

FILE *OpenFile(char *caminho, char *mode)
{
    FILE *input_file;
    
    if(!strcmp(mode, "wb"))
    {
        strcat(caminho, ".comp");
        input_file = fopen(caminho, mode);
    }
    else
    {
        input_file = fopen(caminho, mode);
    }

    if(!input_file)
    {
        printf("error opening file!\n");
        exit(1);
    }

    return input_file;
}

void CloseFile(FILE *f)
{
    fclose(f);
}

void FrequencyCount(unsigned int *array, char *caminho)
{    
    FILE *input_file = OpenFile(caminho, "r");
    char car;

    int codigo_ascii;

    while (!feof(input_file))
    {
        fread(&car, sizeof(char), 1, input_file);

        if(feof(input_file))
        break;

        codigo_ascii = car;
        array[codigo_ascii]++;
    }

    CloseFile(input_file);
}

