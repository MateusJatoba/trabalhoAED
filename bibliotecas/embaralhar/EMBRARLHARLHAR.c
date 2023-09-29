#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"


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

    push(d1,h);
    push(d2,h);
    push(a1,h);
    push(a2,h);
    push(a3,h);
    push(d3,h);
}

int random() { // cada chamada gera um random diferente.
    int r = rand() % 2; // gera int "pseudo"aleatório baseado na seed incializada na primeira chamada.

    return r; // retorna aleatorio entre (0,1).
}

void gerar_seed(){
    int seed = time(NULL);
    printf("seed :%d\n", seed);
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

int main(){

    tp_deck h;

    inicializa_deck(&h);

    DeclaraDeck(&h);

    ver_deck(&h);

    printf("\nEMBARALHAR !\n");

    embaralha_deck(&h);

    ver_deck(&h);

}