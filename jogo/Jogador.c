#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // biblioteca que permite o uso do 'getch()'
#include <locale.h> //biblioteca que permite o uso do 'setlocale()'
#include <windows.h> 
#include <unistd.h>
#include "deck.h"




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


void Iniciar(){
	//Fun��o para o in�cio do jogo
	setlocale(LC_ALL , "");
	system("cls"); // limpa o terminal
	imprimirEfeito("Esses sao os personagens do jogo!!" , 38);
	printf("\n");
	imprimirEfeito("Saphira, fada da lua - Uma fada da lua misteriosa, protetora dos segredos noturnos e figura de magia noturna e tranquilidade na floresta encantada. Poder de curandeira: Comece com mais 5 pontos de Vida\n\n" , 38);

	imprimirEfeito("Grimgar, cavaleiro abissal - Um cavaleiro abissal e habilidoso, vestido com uma armadura negra e um elmo com chifres, cujo passado misterioso o torna temido e respeitado. Investida feroz: Adquira mais 1 ponto de energia\n\n" , 38);

}

void creditos(){

	system("cls");
	
	printf("Professor Orientador:\nMarcio Soussa\n");
	printf("\nAlunos:\n");
	printf("\nBeatriz Rosa\nDavi Passos\nMaria Luiza Queiroz\nMateus Jatoba\n");

	Sleep(1500);

	printf("\nAperte <ENTER> para ver nosso patrocinador");

	int tecla = getch();
	
	if(tecla == 13){
		system("cls");
		char texto[] = "SmartShelf Co."; // Texto dos créditos
    	int delay_microseconds = 100000; // Atraso entre os movimentos
    	int largura_terminal = 90; // Largura do terminal

    
    	for (int i = 0; i < largura_terminal; i++) {// Loop para mover o texto da direita para a esquerda
        
        	for (int j = 0; j < i; j++) {// Imprime espaços em branco para alinhar o texto a direita
            	putchar(' ');
        	}
        
        	printf("%s", texto);// Imprime o texto
       
        	printf("\r"); // Limpa a linha

        	usleep(delay_microseconds);// Espera um curto período de tempo
    	}
	}
	
}




int main(){
	int teclaMenu , aux;
	char nome_jogador[10];
	personagem p;
	
	
	imprimirEfeito("Bem - Vindo ao Nosso Jogo !!!\n" , 38);
	printf("Insira seu nome: ");
	scanf("%s" , nome_jogador);
	
	system("cls");
	
	printf("\nOi, %s. Vamos jogar!!!\n" , nome_jogador);
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


		scanf("%d",&aux);
		inicializa_personagem(&p); // funcao criada para inicializar o personagem com os valores padroes de vida e energia

		switch (aux)
		{
			case 1:
				saphira(&p);
				break;
			case 2:
				grimgar(&p);
				break;

			default:
				break;
		}
		
		printf("\nPontos de Vida: %d\n" , p.vida); // Botei isso aqui p ver se as funcoes estavam funcionando
		printf("Pontos de energia: %d\n" , p.energia);
	}
	
	if(teclaMenu == 27){
		creditos();
	}		
} 
