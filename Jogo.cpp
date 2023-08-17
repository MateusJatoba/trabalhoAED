#include <stdio.h>
#include <conio.h> // biblioteca que permite o uso do 'getch()'
#include <locale.h> //biblioteca que permite o uso do 'setlocale()'
#include <windows.h> //biblioteca que permite o uso das funções para o efeito da frase

void Iniciar(){
	//Função para o início do jogo
	printf("Iniciar");
}

void ESC(){
	//Função para os créditos
	printf("Créditos");
}

void imprimirEfeito(char *txt , int intervalo){ 

// Botei esse efeito para ficar mais apresentável. Quando quiser uma frase com um efeito, bota essa função com o parâmetro do intervalo
	
	for(int i =0 ; txt[i] != '\0' ; i++){
		putchar(txt[i]);
		Sleep(intervalo);
	}
}

int main(){
	int teclaMenu;
	
	setlocale(LC_ALL , ""); // Permição de caracteres especiais (acentuação e etc)
	
	imprimirEfeito("Bem - Vindo ao Nosso Jogo !!!\n" , 70);
	
	Sleep(1000);
	imprimirEfeito("Pressione uma tecla a sua escolha:\n" , 70);
	Sleep(500);
	printf("<ENTER> para Iniciar \n<ESC> para os créditos \n") ;
	
	teclaMenu = getch();
	
	
	if(teclaMenu == 13){
		Iniciar();
	}
	
	if(teclaMenu == 27){
		ESC();
	}		
} 
