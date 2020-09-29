#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

void visita (void *valor){
  printf(" %d ", *(int*)valor);
}

int compara(void *v1, void *v2){
  if(*(int*)v1>*(int*)v2){
    return 1;
  }
  if((int*)v1==(int*)v2){
    return 0;
  }
  else{
    return -1;
  }
}

void printAltura(No* no){
  int niveis;
  niveis = altura(no);
  printf("\n-------Altura do no%d-------\n", *(int*)no->v);
  printf("numero de niveis: %d", niveis);
   printf("\n---------------------------\n");
}

void printPreOrdem(No* no){
  printf("\n---------Pre Ordem---------\n");
  percorrePreOrdem(no, visita);
  printf("\n---------------------------\n");
}

void printPosOrdem(No* no){
  printf("\n---------Pos Ordem---------\n");  
  percorrePosOrdem(no, visita);
  printf("\n---------------------------\n");
}

void printEmOrdem(No* no){
  printf("\n---------Em Ordem---------\n");
  percorreEmOrdem(no, visita);
  printf("\n---------------------------\n");
}

void printLargura(No* no){
  printf("\n---------Largura---------\n");
  percorreLargura(no, visita);
  printf("\n---------------------------\n");
}

void printFatorBalanceamento(No* no){
  int fator;
  printf("\n----Fator de Balanceamento do no%d----\n", *(int*)no->v);
  fator = fatorBalanceamento(no);
  printf("Fator de Balanceamento: %d", fator);
  printf("\n--------------------------------------\n");
}
/*
void printInteracoes(No* no){
  int *chave;
  int aux;
  int interacao;
  printf("Pesquise um valor: \n");
  scanf("%d", &aux);
  *chave = aux;
  interacao = pesquisa(no, chave, compara);
  printf("Numero de interacoes: %d\n", interacao);
}*/

int main(void) {
  Arvore *a;
  a = cria(sizeof(int),compara);
  int valor;

  valor = 5;
  adiciona(a, &valor);

  valor = 3;
  adiciona(a, &valor);

  valor = 7;
  adiciona(a, &valor);

  valor = 2;
  adiciona(a, &valor);

  valor = 4;
  adiciona(a, &valor);

  valor = 1;
  adiciona(a, &valor);

  //valor = 9;
  //No *no9 = adiciona(a, &valor, compara);

  //no8->esquerda = no6;
  //no8->direita = no9;

  /*valor = 5;
  No *no5 = adiciona(a, &valor, compara);

  valor = 7;
  No *no7 = adiciona(a, &valor, compara);

  no6->esquerda = no5;
  no6->direita = no7;
  */
  printPreOrdem(a->raiz);

  printPosOrdem(a->raiz);

  printEmOrdem(a->raiz);

  printLargura(a->raiz);

  //printInteracoes(a->raiz);

  printAltura(a->raiz);

  printFatorBalanceamento(a->raiz);
  

  printf("oi\n");

  return 0;
}