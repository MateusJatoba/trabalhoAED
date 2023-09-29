#ifndef MONSTRODECK_H
#define MONSTRODECK_H
#include <stdio.h>
#define MAX 100


typedef struct 
{
    int monster_id;
    int vida;
    int moveset; // id da lista de movimentos do monstro
} tp_monstro;

typedef struct { /*criando strutura do tipo  carta*/
    int carta_id; /*numeração da carta*/
    int tipo; /*tipo da carta : 1-ataque, 2-defesa, 3-especial*/
    int valor; /*valor da carta*/
    int custo; /*custo da carta*/
}tp_carta; 

typedef struct { /*criando strutura do tipo deck*/
    tp_carta carta[MAX]; /*vetor de tamanho MAX do tipo carta*/
    int topo; /*topo da pilha*/
}tp_deck;

void inicializa_deck(tp_deck *p){
    p->topo = -1; /*definindo que o deck está pronto*/
}

int deck_vazio(tp_deck *p){ 
    if (p->topo == -1) /*se o topo for = -1, está vazio*/
        return 1;
    else 
        return 0;
}

int deck_cheio(tp_deck *p){
    if (p->topo >= MAX) /*se topo for maior ou igual MAX, está cheia*/
        return 1;
    else
        return 0;
}

int push(tp_carta e,tp_deck *p){ /*adiciona uma carta no deck*/
    if(p->topo + 1 <= MAX){ /*se tem espaço*/
        (p->topo)++; /*define "novo" topo*/
        p->carta[p->topo] = e; /*adiciona a carta 'e' no deck*/
        return 1;    
    } 
    else return 0; /*sem espaço*/
}

int pop(tp_carta *e,tp_deck *p){ /*retira o valor do ultimo item da pilha*/
    if ((p->topo) < 0) /*se a pilha está vazia*/
        return 0;
    else{
        *e = p->carta[p->topo]; /*var.'e' vai receber o valor do item do topo*/
        (p->topo)--; /*diminui o topo "apagando" o valor do item */
        return 1;
}
}

int top(tp_carta *e, tp_deck *p){ /*apenas copia o valor do ultimo item da pilha*/
    if ((p->topo) < 0) /*se a pilha está vazia*/
        return 0;
    else{ 
        *e = p->carta[p->topo]; /*var.'e' vai receber o valor do item do topo*/
        return 1;
}
}

int altura_deck(tp_deck *p){ /*mostra o tamanho da pilha*/
    return p->topo + 1;
}

void empilha_deck(tp_deck *p, tp_deck *p2){
tp_deck aux;
tp_carta e;

    inicializa_deck(&aux);

    if (altura_deck(p) + altura_deck(p2) > MAX)
        printf("\n impossivel realizar essa funcao! limite atingido \n");
    else {
        while (!deck_vazio(p2)){ 
            pop(&e,p2);
            push(e,&aux);
        }
        while (!deck_vazio(&aux)){ 
            pop(&e,&aux);
            push(e,p);
        }
    }
} 

void ver_deck(tp_deck *p) {
    tp_carta e;
    tp_deck aux;

    inicializa_deck(&aux);

    while(!deck_vazio(p)){
        pop(&e,p);
        printf("\n Carta: %i",e.carta_id);
        printf("\n Tipo: %i",e.tipo);
        printf("\n Custo: %i",e.custo);
        printf("\n Valor: %i \n",e.valor);
        push(e,&aux);
    }
    while(!deck_vazio(&aux)){
        pop(&e,&aux);
        push(e,p);
    }
            
}


#endif
