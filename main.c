/*
 * =======================================================
 *  Arquivo: main.c
 *  Autor: Bruno Vale Lourenço
 *  OBSERVAÇÕES: considerei que o caminho passado para leitura das pastas de entrada seria através do argv[1], então rodei o 
 *  programa assim: ./meu_programa test0, ./meu_programa test1 ...etc. O único arquivo de saída gerado é o "saida.txt", que é criado de acordo com o "test0; test1 ..." da entrada e produzido na pasta raíz.
 *  O arquivo "saida.txt" é sobrescrito toda vez que o programa é rodado.
 * =======================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "booked.h"

int main(int argc, char *argv[])
{
    int stop, flag = 0;
    int vet_comandos[4]; //guarda cada ID dos comandos.

    tBooked *booked = BookedConstruct(argv[1]);
    UpdateAfinidades(booked);

    FILE *comandos_file = OpenFile(argv[1], "comandos.txt", 'r');
    //arquivo de saída.
    FILE *stdout_file = OpenFile(" ", "saida.txt", 'w');

    while (1)
    {
        stop = Le_Comando(comandos_file, vet_comandos, flag);
        
        flag++;

        if (!stop)
        {
            break;
        }

        ExecutaBooked(vet_comandos, stdout_file, booked);
    }

    CloseFile(comandos_file);
    CloseFile(stdout_file);

    BookedDestroy(booked);

    return 0;
}


