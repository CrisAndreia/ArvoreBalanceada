#include <stdio.h>
#include <stdlib.h>

typedef struct no {
  struct no *pai;
  struct no *esquerda;
  struct no *direita;
  float *v;
} No;

typedef struct arvore {
  No *raiz;
} Arvore;

Arvore* cria(int tamanho, int (compara)(void *, void *) );
No* adiciona(Arvore *arvore, void *valor);
void percorrePreOrdem(No* no, void (visita)(void *valor));
void percorrePosOrdem(No* no, void (visita)(void *valor));
void percorreEmOrdem(No* no, void (visita)(void *valor));
void percorreLargura(No* no, void (visita)(void *valor));
void ordemCresce(No* no1, No* no2, void (compara)(void *v1, void *v2));
int pesquisa(No *no, void *valor, int (compara)(void *v1, void *v2));
No* localiza(No *no, void *valor, int (compara)(void *v1, void *v2));
int altura(No* no);
int fatorBalanceamento (No* no);
void rotacaoSimplesEsquerda(No* no);
void rotacaoSimplesDireita(No* no);