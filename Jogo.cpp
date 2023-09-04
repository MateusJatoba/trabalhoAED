#include <stdio.h>
#include <conio.h> // biblioteca que permite o uso do 'getch()'
#include <locale.h> //biblioteca que permite o uso do 'setlocale()'
#include <windows.h> //biblioteca que permite o uso das fun��es para o efeito da frase

void Iniciar(){
	//Fun��o para o in�cio do jogo
	printf("Iniciar");
}

void ESC(){
	//Fun��o para os cr�ditos
	printf("creditos");
}

void imprimirEfeito(char *txt , int intervalo){ 

// Botei esse efeito para ficar mais apresent�vel. Quando quiser uma frase com um efeito, bota essa fun��o com o par�metro do intervalo
	
	for(int i =0 ; txt[i] != '\0' ; i++){
		putchar(txt[i]);
		Sleep(intervalo);
	}
}

int main(){
	int teclaMenu;
	
	setlocale(LC_ALL , ""); // Permi��o de caracteres especiais (acentua��o e etc)
	
	imprimirEfeito("Bem - Vindo ao Nosso Jogo !!!\n" , 38);
	
	Sleep(500);
	imprimirEfeito("Pressione uma tecla a sua escolha:\n" , 38);
	Sleep(500);
	printf("<ENTER> para Iniciar \n<ESC> para os creditos \n") ;
	
	teclaMenu = getch();
	
	
	if(teclaMenu == 13){
		Iniciar();
	}
	
	if(teclaMenu == 27){
		ESC();
	}		
} 
