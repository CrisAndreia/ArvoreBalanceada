#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
  struct no *pai;
  struct no *esquerda;
  struct no *direita;
  void *v;
} No;

typedef struct arvore {
  No *raiz;
  int tamanho;

  int (*compara)(void *, void *);
} Arvore;

void balanceamento (No* no);

Arvore* cria(int tamanho, int (compara)(void *, void *) ) {
  Arvore *arvore = malloc(sizeof(Arvore));
  arvore->raiz = NULL;
  arvore->tamanho = tamanho;
  arvore->compara = compara;
  
  return arvore;
}

int vazia(Arvore* arvore) {
  return (arvore->raiz == NULL);
}

No* localiza(Arvore *arvore, No *no, void *valor) {
  if (arvore->compara(valor,no->v) > 0) {
    if (no->direita != NULL) {
      return localiza(arvore, no->direita, valor);
    }
  } else {
    if (no->esquerda != NULL) {
      return localiza(arvore, no->esquerda, valor);
    }
  }

  return no;
}
/*
No* adiciona(Arvore *arvore, void *valor) {
  No *pai = NULL;

  if (arvore->raiz != NULL) {
    pai = localiza(arvore, arvore->raiz, valor);
  }

  No *no = malloc(sizeof(No));
  no->pai = pai;
  
  no->esquerda = NULL;
  no->direita = NULL;
  
  no->v = malloc(arvore->tamanho);
  memcpy(no->v,valor,arvore->tamanho);

  if (pai == NULL) {
    arvore->raiz = no;
  } else {
    if (arvore->compara(no->v,pai->v) > 0) {
      pai->direita = no;
    } else {
      pai->esquerda = no;
    }
  }

  balanceamento(no);
  
  return no;
}*/

No* adiciona(Arvore *arvore, void *valor) {
  No *pai = NULL;

  if (arvore->raiz != NULL) {
    pai = localiza(arvore, arvore->raiz, valor);
  }

  No *no = malloc(sizeof(No));
  no->pai = pai;
  
  no->esquerda = NULL;
  no->direita = NULL;
  
  no->v = malloc(arvore->tamanho);
  memcpy(no->v,valor,arvore->tamanho);

  if (pai == NULL) {
    arvore->raiz = no;
  } else {
    if (arvore->compara(no->v,pai->v) > 0) {
      pai->direita = no;
    } else {
      pai->esquerda = no;
    }
  }

  balanceamento(no);
  
  return no;
}

void percorrePreOrdem(No* no, void (visita)(void *valor)) {
  if (no != NULL) {
    visita (no->v);

    //printf("%f ", no->v);
    percorrePreOrdem(no->esquerda, visita);
    percorrePreOrdem(no->direita, visita);
  }
}

void percorreEmOrdem(No* no, void (visita)(void *valor)) {
  if (no != NULL) {
    //printf("%f ", no->v);
    percorreEmOrdem(no->esquerda, visita);
    visita (no->v);
    percorreEmOrdem(no->direita, visita);
    
  }
}

void percorrePosOrdem(No* no, void (visita)(void *valor)) {
  if (no != NULL) {
    //printf("%f ", no->v);
    percorrePosOrdem(no->esquerda, visita);
    percorrePosOrdem(no->direita, visita);

    visita (no->v);
  }
}

void percorreLargura(No* no, void (visita)(void *valor)) {
  No **nivel = malloc(sizeof(No));
  nivel[0] = no;

  int tam = 1;

  while(tam != 0) {
    int filhos = 0;

    for(int i = 0; i < tam; i++){
      if (nivel[i]->esquerda != NULL){
        filhos++;
      }

      if (nivel[i]->direita != NULL){
        filhos++;
      }
    }
    No** nos = malloc(filhos * sizeof(No));
    filhos = 0;
    
    for(int i = 0; i < tam; i++){
      if (nivel[i]->esquerda != NULL){
        nos[filhos++] = nivel[i]->esquerda;
      }

      if (nivel[i]->direita != NULL){
        nos[filhos++] = nivel[i]->direita;
      }

      visita(nivel[i]->v);
    }

    free(nivel);
    
    nivel = nos;
    tam = filhos;
  }
}
void ordemCresce(No* no1, No* no2, void (compara)(void *v1, void *v2)){
  compara(no1->v, no2->v);
}

int pesquisa(No *no, void *valor, int (compara)(void *v1, void *v2)) {
  int cont=0;
  if (compara(valor, no->v) == 0){
    cont++;
    return cont;
  }
  if (compara(valor,no->v) > 0) {
    cont++;
    pesquisa(valor, no->direita,compara);
  }
  else {
    cont++;
    pesquisa(valor, no->esquerda,compara);
  }
  return cont;
}

int altura(No* no) {
  int contDireita=0, contEsquerda=0;

  if (no != NULL) {
    if(no->esquerda!=NULL){
      contEsquerda = altura(no->esquerda) + 1;

    }
    if(no->direita!=NULL){
      contDireita = altura(no->direita) + 1;
    }
  }

  if(contEsquerda > contDireita){
    return contEsquerda;
  }
  else{
    return contDireita;
  }
  
}

int fatorBalanceamento (No* no){
  int esquerda = 0;
  int direita = 0;

  if (no->direita != NULL) {
    direita = altura(no->direita)+1;
  }

  if (no->esquerda != NULL) {
    esquerda = altura(no->esquerda)+1;
  }

  return esquerda - direita;
}

void rotacaoSimplesEsquerda(No* no){
  No* pai;
  No* esquerda;
  //No* filhoDireita;
  No* filhoEsquerda;

  esquerda = no;
  pai = no->direita;
  filhoEsquerda = pai->esquerda;

  no->pai = pai;
  pai->esquerda = esquerda;
  no->esquerda = filhoEsquerda;
  
}

void rotacaoSimplesDireita(No* no){
  No* pai;
  No* direita;
  //No* filhoDireita;
  No* filhoDireita;

  direita = no;
  pai = no->esquerda;
  filhoDireita = pai->direita;

  no->pai = pai;
  pai->direita = direita;
  no->direita = filhoDireita;
  
}

void balanceamento(No *no) {
  if (no != NULL) {
    int fator = fatorBalanceamento(no);
    printf("FB(%d) = %d\n",*(int*) no->v, fator);
    
    if (fator > 1) {
      fator = fatorBalanceamento(no->esquerda);

      if (fator > 0) {
        printf("RSD %d\n", *(int*) no->v);
      } else {
        printf("RDD %d\n", *(int*) no->v);
      }
    } 
    else {
      if (fator < -1){
        fator = fatorBalanceamento(no->direita);
        if (fator < 0) {
          printf("RSE %d\n", *(int*) no->v);
          rotacaoSimplesEsquerda(no);
        }else {
          printf("RDE %d\n", *(int*) no->v);
          rotacaoSimplesDireita(no);
        }
      }
    }
    balanceamento(no->pai);
  }
  //balanceamento(no->pai);
}