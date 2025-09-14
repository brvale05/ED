/** 
 * @file listaArvores.c
 * @author Bruno Vale e Davi sena
 */

#include <stdio.h>
#include <stdlib.h>

#include "listaArvores.h"

typedef struct Celula Celula;

struct Celula{

    Arv *a;
    Celula *prox;
};

struct Lista{

    Celula *prim;
    Celula *ult;
    int tamanho;
};

int lista_vazia(Lista *l){

    return l->prim == NULL;
}

Lista *criaLista(){

    Lista* l = (Lista*) malloc(sizeof(Lista));
    l->prim = l->ult = NULL;
    l->tamanho = 0;

    return l;

}

void *insereNaLista(Arv* a, Lista* Lista){
    //insere uma arvore na lista ordenando de acordo com a frequencia

    Celula* novo = (Celula*) malloc(sizeof(Celula));
    novo->a = a;
    novo->prox = NULL;

    if (lista_vazia(Lista)){ //lista vazia

        Lista->prim = Lista->ult = novo;
        

    } else if(frequencia_arv(a) < frequencia_arv(Lista->prim->a)){ //caso a frequencia da nova arvore seja menor

        novo->prox = Lista->prim;
        Lista->prim = novo;

    } else{ // caso seja necessario percorrer a lista (frequencia entre o menor e maior)

        Celula *aux;
        aux = Lista->prim;

         //comparação ate achar onde a arv se encaixa
        while(aux->prox != NULL && frequencia_arv(a) >= frequencia_arv(aux->prox->a)){

            aux = aux->prox;

        }
        //encaixa a arv na lista
        novo->prox = aux->prox;
        aux->prox = novo;

        if(novo->prox == NULL){ //verifica se a nova arv ta no final da lista

            Lista->ult = novo;
        }


    }

    Lista->tamanho++;


}

void juncao_arvs_lista(Lista *l, int eh_unicaArvore){

    if(eh_unicaArvore)
    {
        return;
    }

    while(l->tamanho > 1){

        Arv *juncao = criaArv_vazia();

        juncao = junta_arvs(l->prim->a, l->prim->prox->a);

        retira_duasArv_Da_Lista(l);

        insereNaLista(juncao, l);
    }

}

void retira_duasArv_Da_Lista(Lista *l){ //retira a primeia e a segunda arv da lista (juncao)

    if(lista_vazia(l)){

        return;

    } else {

        Celula *prim = l->prim;
        Celula *aux = prim->prox;

        l->prim = aux->prox;

        free(prim);
        free(aux);

        l->tamanho -=2; //menos duas arv na lista

    }

}

void desalocaLista(Lista *l){

    Celula *prim = l->prim;
    Celula *prox;

    while(prim != NULL){

        prox = prim->prox;
        libera_arv(prim->a);
        free(prim);
        prim = prox;

    }

    free(l);
}

Arv *retorna_Prim_arv(Lista *l){

    return l->prim->a;
}

int unico_elem_lista(Lista *l)
{
    Celula *aux = l->prim;

    if(aux->prox == NULL)
    {
        return 1;
    }

    return 0;

}