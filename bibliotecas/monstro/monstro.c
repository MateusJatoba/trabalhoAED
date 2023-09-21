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

int main(){

    tp_monstro jeff;
    jeff.monster_id = 1;
    jeff.vida = 100;
    jeff.moveset = 1;

    mostrarMonstro(&jeff);

}