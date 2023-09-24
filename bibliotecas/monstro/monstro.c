#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // biblioteca que permite o uso do 'getch()'
#include <locale.h> //biblioteca que permite o uso do 'setlocale()'
#include <windows.h> 
#include "deck.h"


void mostrarMonstro(tp_monstro *m){
    if(m->monster_id == 1){//Montro 1 tem nome de JEFF
        m->vida = 100; // declarando a vida do monstro
        m->moveset = 1;
        printf("JEFF");
        printf("\nVIDA:100");
    }
}

void mostrarAcao(int rodada){
    
    char movSelect; // Tipo de movimento (ataque, defesa e especial)
    int ValSelect; // Valor de cada movimento
    char mov[3] = {'a','d','e'};
    int val[3] = {6,8,3};

    if(rodada > 3){
        rodada = rodada-3;
    }

    movSelect = mov[rodada-1];
    ValSelect = val[rodada-1];
        
    switch (movSelect){
        case 'a':
            printf("\nVai Atacar = %i", ValSelect);
            break;
        case 'd':
            printf("\nVai Defender = %i", ValSelect);
            break;
        case 'e':
            printf("\nVai Lançar Magia = %i", ValSelect);
            break;

        default:
            break;
    }
}

int passarRodada(int *rodada){
    char s; // variavel auxiliar
    printf("\n\nPARA PASSAR A RODADA APERTE <ENTER>\n\n");
    s = getch(); // resgata a tecla digitada
    if(s == 13){ // se apertar enter a rodada eh incrementada
        (*rodada) ++;
        return 1;
    }
    else{
        return 0;
    }
}

int main(){

    setlocale(LC_ALL , "portuguese");
    int rodada = 1;
    tp_monstro jeff;

    jeff.monster_id = 1;

    mostrarMonstro(&jeff);//primeira movimentacao
    mostrarAcao(rodada);//primeira movimentacao

    while(passarRodada(&rodada) != 0){//movimentacao ate a funcao retornar 0 -> Quando o usuario n apertar enter
        mostrarMonstro(&jeff);
        mostrarAcao(rodada);
        rodada+=1;
    }

    printf("\nstop");
}