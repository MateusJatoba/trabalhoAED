#ifndef MAO_H
#define MAO_H
#include <stdio.h>
#include <stdlib.h>
#include "embaralhadeck.h"


typedef struct tp_no{
   tp_carta info;
  struct tp_no *prox;
} tp_mao;

tp_mao *inicializa_mao(){
  return NULL;
}

int mao_vazia(tp_mao *mao_jogador){
  if(mao_jogador==NULL) return 1;
  return 0;
}

tp_mao *aloca_listase(){
  tp_mao *novo_no;
  novo_no = (tp_mao*) malloc(sizeof(tp_mao));
  return novo_no;
}

int insere_mao_no_fim(tp_mao **l , tp_carta e){
  tp_mao *novo_no, *atu;
  novo_no = aloca_listase(); // aqui está pegando o novo nó e apontando para NULL
  if(novo_no == NULL) return 0; // não alocou memória
  // atribuir os valores para novo nó:
  novo_no -> info = e;
  novo_no -> prox = NULL;
  // finaliza o encadeamento do nó
  if(mao_vazia(*l)){ // se for o primeiro nó entra aqui
    *l = novo_no;
  } else {
    atu = *l;
    while (atu -> prox!=NULL){
      atu = atu -> prox; // aponta para o último nó
    }
    atu -> prox = novo_no;// o ultimo ponteiro apontará para a memoria alocada
  }
  return 1;
}


int remove_mao(tp_mao **mao_jogador, tp_carta e){  
 tp_mao *ant, *atu;
  atu= *mao_jogador;
  ant= NULL;
  
  while((atu!=NULL)&&(atu->info.carta_id != e.carta_id)){
    ant=atu;
    atu=atu->prox;
  }
  
  if (atu==NULL) return 0; //nao foi encontrado o elemento
  
  if (ant==NULL){ //se for retirado o primeiro termo
      *mao_jogador = atu->prox; //fazendo a lista apontar para o termo subsequente e nao ficar vazia depois de remover o primeiro elemente 
  }
    else{
      ant->prox = atu->prox; //faz com que o o proximo aponte para o prox do prox
  }
  
  free(atu);
  atu=NULL;
  return 1;
}




int tamanho_mao(tp_mao *mao_jogador){
  int cont=0;
  tp_mao *atu;
  atu=mao_jogador;
  while(atu!=NULL){
    cont ++;
    atu=atu->prox;
  }
  return cont;
}

void destroi_mao(tp_mao **m){
  tp_mao *atu;
  atu=*m;
  while(atu!=NULL){
    *m=atu->prox;
    free(atu);
    atu=*m;
  }
}

void imprime_mao(tp_mao *mao_jogador) {
    tp_mao *atu = mao_jogador;

    while (atu != NULL) {
        printf("Carta ID: %d\n", atu->info.carta_id);
        printf("Tipo: %d\n", atu->info.tipo);
        printf("Valor: %d\n", atu->info.valor);
        printf("Custo: %d\n", atu->info.custo);
        printf("\n");

        atu = atu->prox;
    }
}


/////////////////////////////////////////////////////////////////////


void cava(tp_mao **mao_jogador, tp_carta e){
  int i;
  tp_deck h;
  inicializa_deck(&h);
  DeclaraDeck(&h);
  embaralha_deck(&h);
  *mao_jogador = inicializa_mao();
  for (i=0; i<5; i++){
    pop(&e,&h);
    insere_mao_no_fim(mao_jogador, e);
  }
}

void descarte_deck(tp_mao *mao_jogador, tp_carta e){
  tp_deck descarte;
  inicializa_deck(&descarte);
  remove_mao(&mao_jogador, e);
  push(e, &descarte);
}

void retorna_deck(tp_deck *descarte, tp_deck *h, tp_carta e){
  embaralha_deck(descarte);
  while(!deck_vazio(descarte)){
    pop(&e, descarte);
    push(e,h);
  }
}

#endif