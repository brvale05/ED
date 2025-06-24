#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "booked.h"

int main(int argc, char *argv[])
{
    int stop, flag = 0;
    int vet_comandos[4];

    tBooked *booked = BookedConstruct(argv[1]);
    UpdateAfinidades(booked);

    FILE *comandos_file = OpenFile(argv[1], "comandos.txt", 'r');
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


