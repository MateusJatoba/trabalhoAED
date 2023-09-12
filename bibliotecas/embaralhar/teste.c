#include <stdio.h>
#include "deck.h"

// void embaralhar()

// void descarte()

// void comprar()


int main(){
    int x, y;

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
    a3.carta_id = 5;
    a3.valor = 4;
    a3.tipo = 1;
    a3.custo = 1;

    tp_carta d1;
    d1.carta_id = 3;
    d1.valor = 3;
    d1.tipo = 2;
    d1.custo = 2;

    tp_carta d2;
    d2.carta_id = 4;
    d2.valor = 2;
    d2.tipo = 2;
    d2.custo = 1;

    tp_carta d3;
    d3.carta_id = 6;
    d3.valor = 7;
    d3.tipo = 2;
    d3.custo = 3;

    tp_deck h;

    inicializa_deck(&h);

    push(d1,&h);
    push(d2,&h);
    push(a1,&h);
    push(a2,&h);
    push(a3,&h);
    

    scanf("%i", &x);

    if (x==1)
        ver_deck(&h);

    else
        printf("error");

    scanf("%i", &y);

    if (y==1){
        push(d3,&h);
        ver_deck(&h);
    }
    
    else
        printf("error");


    

}