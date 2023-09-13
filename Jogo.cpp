#include <stdio.h>
#include <conio.h> // biblioteca que permite o uso do 'getch()'
#include <locale.h> //biblioteca que permite o uso do 'setlocale()'
#include <windows.h> 
#include "deck.h"




void imprimirEfeito(char *txt , int intervalo){ 

// Botei esse efeito para ficar mais apresent�vel. Quando quiser uma frase com um efeito, bota essa fun��o com o par�metro do intervalo
	
	for(int i =0 ; txt[i] != '\0' ; i++){
		putchar(txt[i]);
		Sleep(intervalo);
	}
}


void Iniciar(){
	//Fun��o para o in�cio do jogo
	system("cls");
	imprimirEfeito("Esses sao os personagens do jogo!!" , 38);
	printf("\n");
	imprimirEfeito("Saphira, fada da lua - Saphira é uma fada da lua misteriosa, guardiã dos segredos noturnos e símbolo de magia noturna e tranquilidade na floresta encantada. Poder de curandeira: Comece com mais 5 pontos de Vida\n\n" , 15);
	imprimirEfeito("Grimgar, cavaleiro abissal - Grimgar é um cavaleiro abissal enigmático e habilidoso, vestido com uma armadura negra e um elmo com chifres, cujo passado misterioso o torna temido e respeitado. Investida feroz: Adquira mais 1 ponto de energia\n\n" , 15);
	imprimirEfeito("Zephir, mestre dos ventos - Zephir é um mestre do vento com cabelos prateados e olhos claros, hábil no controle de correntes de ar e na busca da calma na tempestade. Poder: Consiga mais uma carta no deck de batalha\n\n" , 15);
	
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
				p.vida += 5;
				break;
			case 2:
				p.energia += 1;
				break;
				
			case 3:
				// int *pont = malloc(sizeof(int) * 5);
				// int *novo_vetor = realloc(pont, sizeof(int) * 10);

				// realloc(p.deckPrincipal)
				break;

			
			default:
				break;
		}
		printf("%d" , p.vida);
	}
	
	if(teclaMenu == 27){
		ESC();
	}		
} 
