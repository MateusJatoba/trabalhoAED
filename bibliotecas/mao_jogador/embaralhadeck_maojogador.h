#ifndef EMBARALHADECK_H
#define EMBARALHADECK_H
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 100


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


void DeclaraDeck(tp_deck *h) {

    tp_carta a1;
    a1.carta_id = 1;
    a1.valor = 3;
    a1.tipo = 1;
    a1.custo = 1;

    tp_carta a2; 
    a2.carta_id = 2;
    a2.valor = 5;
    a2.tipo = 1;
    a2.custo = 2;

    tp_carta a3;
    a3.carta_id = 3;
    a3.valor = 4;
    a3.tipo = 1;
    a3.custo = 1;

    tp_carta a4;
    a4.carta_id = 4;
    a4.valor = 6;
    a4.tipo = 1;
    a4.custo = 3;

    tp_carta d1;
    d1.carta_id = 5;
    d1.valor = 3;
    d1.tipo = 2;
    d1.custo = 2;

    tp_carta d2;
    d2.carta_id = 6;
    d2.valor = 2;
    d2.tipo = 2;
    d2.custo = 1;

    tp_carta d3;
    d3.carta_id = 7;
    d3.valor = 7;
    d3.tipo = 2;
    d3.custo = 3;

    tp_carta d4;
    d4.carta_id = 8;
    d4.valor = 9;
    d4.tipo = 2;
    d4.custo = 4;

    push(d4,h);
    push(d3,h);
    push(d2,h);
    push(d1,h);
    push(a4,h);
    push(a3,h);
    push(a2,h);
    push(a1,h);
}

int random() { // cada chamada gera um random diferente.
    int r = rand() % 2; // gera int "pseudo"aleatório baseado na seed incializada na primeira chamada.

    return r; // retorna aleatorio entre (0,1).
}

void gerar_seed(){
    int seed = time(NULL);
    printf("\n-----------------\nseed :%d\n-----------------\n", seed);
    srand(seed); // semente gerada 
}

void embaralha_deck(tp_deck *h){ //recebe um deck e retorna o mesmo embaralhado.
    tp_deck aux1, aux2; // declaração de estruturas auxiliares.
    tp_carta e; // ...
    int x; // ...
    int i; // ...
    inicializa_deck(&aux1); // inicializa deck aux
    inicializa_deck(&aux2);// ...
    gerar_seed(); // gera seed para o srand

    for (i = 0; i < 5; i++) // embaralha 5 vezes.
    {
        while(!deck_vazio(h)){ // esvazia o deck h.
            pop(&e,h);
            x = random(); 
            if(x == 1){
                push(e,&aux1); // add carta e no deck aux 1 se for 1.
            }
            else{
                push(e,&aux2); // add carta e no deck aux 2 se for 0.
            }
        }

        empilha_deck(&aux1, &aux2); // empilha aux 1 e aux 2

        while(!deck_vazio(&aux1)){
            pop(&e,&aux1);
            push(e,h); // insere o aux1 no deck
        }
    }
}


#endif
