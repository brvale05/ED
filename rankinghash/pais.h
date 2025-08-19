#ifndef PAIS_H
#define PAIS_H

#define TAM_MAX 100

typedef struct Country Country;

typedef Country* Hash[TAM_MAX];

void hash_inicializa(Hash ranking);

Country *hash_insere(Hash ranking, char *nome, int ouro, int prata, int bronze, int total);

int hash_id(char *chave);

void hash_libera(Hash ranking);

int conta_qtd_paises(Hash ranking);

int compara_paises(const void *p1, const void *p2);

void imprime_pais(Country *ctry);

void adiciona_vetor(Hash ranking, Country **vetor);

void escreve_saida(Country **vetor, int tam);

#endif