#ifndef ARVORE_H
#define ARVORE_H

#define EH_FOLHA 1

typedef struct Arvore Arvore;

Arvore *TreeConstruct(int codigo, int num_eventos, int ehfolha);

Arvore *TreePushBack(Arvore *raiz1, Arvore *raiz2);

// void TreePrint(Arvore *arv);

void BinaryTreePrint(Arvore *arv);

Arvore *BinaryTreeDestroy(Arvore *arv);

int TreesCompare(const void *t1, const void *t2);

int TreeHeight(Arvore *raiz);

bitmap *BinaryCode(Arvore *raiz, int *array, int id);

#endif