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

    else if (m->monster_id == 2)//monstro 2 tem nome de JHONNY
    {
        m->vida = 200;//declarando a vida
        m->moveset = 2;
        printf("JHONNY\n");
        printf("VIDA: %d" , m->vida);
    }
    
}

void mostrarAcao(int rodada){

    tp_monstro monstro;

    monstro.monster_id = 1;

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
            mostrarMonstro(&monstro);//chamando a funcao para mostrar o monstro
            printf("\nVai Atacar = %i", ValSelect);
            break;
        case 'd':
            mostrarMonstro(&monstro);//chamando a funcao para mostrar o monstro
            printf("\nVai Defender = %i", ValSelect);
            break;
        case 'e':
            mostrarMonstro(&monstro);//chamando a funcao para mostrar o monstro
            printf("\nVai Lançar Magia = %i", ValSelect);
            break;

        default:
            break;
    }


    int passarRodada(){//n possui parametro
        char s; // variavel auxiliar
        printf("\n\nPARA PASSAR A RODADA APERTE <ENTER>\n\n");
        s = getch(); // resgata a tecla digitada
        if(s == 13){ // se apertar enter a rodada eh incrementada
            
            mostrarAcao(rodada + 1); //usando a recursividade, incrementa a rodada automaticamente 
            return 1;
        }
        else{
            return 0; // encerra a funcao
        }
    }

    passarRodada(); //novo chamado para que n precise de uma estrutura de repeticao
   
}


int main(){

    setlocale(LC_ALL , "portuguese");
    int rodada = 1;

    mostrarAcao(rodada);
    
    printf("\nstop");
}