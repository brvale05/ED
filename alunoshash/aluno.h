#ifndef ALUNO_H
#define ALUNO_H

#define TAM_MAX 300

typedef struct Aluno Aluno;

typedef Aluno *Hash[TAM_MAX];

Aluno *hash_insere(Hash turma, char *nome);

void hash_inicializa(Hash turma);

int hash(char *chave);

void hash_libera(Hash turma);

void imprime_aluno(Aluno *a, FILE *output);

void atualiza_frequencia(Hash turma, char *nome, char frequencia);

void hash_imprime(Hash turma);

#endif