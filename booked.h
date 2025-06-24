#ifndef BOOKED_H
#define BOOKED_H

#include "leitor.h"
#include "utils.h"

typedef struct booked tBooked;

tBooked *BookedConstruct(char *caminho);

void BookedDestroy(tBooked *booked);

int Le_Comando(FILE *comando_file, int *vet, int flag);

void ExecutaBooked(int *vet, FILE *stdout_file, tBooked *booked);

void UpdateAfinidades(tBooked *booked);

#endif