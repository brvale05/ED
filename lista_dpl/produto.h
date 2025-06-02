#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct Produto Produto;

Produto* CriaProduto(char *nome, float preco, int codigo);

float GetPrecoProduto(Produto *p);

char* GetNomeProduto(Produto *p);

int GetCodigoProduto(Produto *p);

void LiberaProduto(Produto *p);

Produto* LeProduto();

void ImprimeProduto(Produto *p);

#endif