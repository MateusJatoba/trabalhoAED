#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // biblioteca que permite o uso do 'getch()'
#include <locale.h> //biblioteca que permite o uso do 'setlocale()'
#include <windows.h> 
#include "deck.h"


void mostrarMonstro(tp_monstro *m){
    if(m->monster_id == 1){
        printf("JEFF");
        printf("\nVIDA:100");
    }
}

void mostrarAcao(tp_monstro m, int rodada){
    char movSelect;
    int ValSelect;
    char mov[3] = {'a','d','e'};
    int val[3] = {6,8,3};

    if(rodada > 3){
        rodada = rodada-2;
    }

    movSelect = mov[rodada-1];
    ValSelect = val[rodada-1];
        
    switch (movSelect){
        case 'a':
            printf("\nVai Atacar= %i", ValSelect);
            break;
        case 'd':
            printf("\nVai Defender= %i", ValSelect);
            break;
        case 'e':
            printf("\nVai Lançar Magia= %i", ValSelect);
            break;

        default:
            break;
    }
}

    void passarRodada(int *rodada){
        char s;
        printf("\n\n\n\n PARA PASSAR A RODADA APERTE X");
        scanf("%c", &s);
        if(s=='x'){
            rodada=rodada+1;
        }
    }

int main(){

    int rodada = 1;

    tp_monstro jeff;
    jeff.monster_id = 1;
    jeff.vida = 100;
    jeff.moveset = 1;

    while(rodada<=1){
        mostrarMonstro(&jeff);
        mostrarAcao(jeff,rodada);
        passarRodada(&rodada);
    }

    printf("stop");

}