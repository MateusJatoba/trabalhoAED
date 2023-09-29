#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // biblioteca que permite o uso do 'getch()'
#include <locale.h> //biblioteca que permite o uso do 'setlocale()'
#include <windows.h> 
#include "deck.h"

using namespace std;


void imprimirEfeito(char *txt , int intervalo){ 

// Botei esse efeito para ficar mais apresent�vel. Quando quiser uma frase com um efeito, bota essa fun��o com o par�metro do intervalo
				
	int i = 0;

    while (txt[i] != '\0') {
        if (_kbhit()) { // Verifica se alguma tecla foi pressionada para retirar o efeito
            char ch = _getch(); // Lê a tecla pressionada
            if (ch == '\r') { // Se Enter foi pressionado, continue imprimindo sem Sleep
                putchar(txt[i]);
                i++;
                while (txt[i] != '\0' && txt[i] != '\n') {
                    putchar(txt[i]);
                    i++;
                }
            }
        } else {
            putchar(txt[i]);
            Sleep(intervalo);
            i++;
        }
    }
}

void saphira(personagem *p){
	p->vida += 5;
}

void grimgar(personagem *p){
	p->energia ++;
}

void zephir(personagem *p){
	//verificar o especial
	
 }

void Iniciar(){
	//Fun��o para o in�cio do jogo
	system("cls");
	imprimirEfeito("Esses sao os personagens do jogo!!" , 38);
	printf("\n");
	imprimirEfeito("Saphira, fada da lua - Saphira é uma fada da lua misteriosa, guardiã dos segredos noturnos e símbolo de magia noturna e tranquilidade na floresta encantada. Poder de curandeira: Comece com mais 5 pontos de Vida\n\n" , 38);
	imprimirEfeito("Grimgar, cavaleiro abissal - Grimgar é um cavaleiro abissal enigmático e habilidoso, vestido com uma armadura negra e um elmo com chifres, cujo passado misterioso o torna temido e respeitado. Investida feroz: Adquira mais 1 ponto de energia\n\n" , 38);
	imprimirEfeito("Zephir, mestre dos ventos - Zephir é um mestre do vento com cabelos prateados e olhos claros, hábil no controle de correntes de ar e na busca da calma na tempestade. Poder: Consiga mais uma carta no deck de batalha\n\n" , 38);
	
}

void ESC(){
	//Fun��o para os cr�ditos
	printf("creditos");
}



int main(){
	int teclaMenu , aux;
	personagem p;
	
	setlocale(LC_ALL , ""); // Permi��o de caracteres especiais (acentua��o e etc)
	
	imprimirEfeito("Bem - Vindo ao Nosso Jogo !!!\n" , 38);
	
	Sleep(500);
	imprimirEfeito("Pressione uma tecla a sua escolha:\n" , 38);
	Sleep(500);
	printf("<ENTER> para Iniciar \n<ESC> para os creditos \n") ;
	
	teclaMenu = getch();
	
	
	if(teclaMenu == 13){
		Iniciar();
		imprimirEfeito("Escolha seu personagem!!!\n" , 38);
		printf("1 - Saphira\n");
		printf("2 - Grimgar\n");
		printf("3 - Zephyr\n");

		scanf("%d",&aux);

		switch (aux)
		{
			case 1:
				saphira(&p);
				break;
			case 2:
				grimgar(&p);
				break;
				
			// case 3:
				
			// 	zephir(&p);
			// 	break;
			default:
				break;
		}
		
		printf("%d " , p.vida); // Botei isso aqui p ver se as funcoes estavam funcionando
		printf("%d " , p.energia);
	}
	
	if(teclaMenu == 27){
		ESC();
	}		
} 
