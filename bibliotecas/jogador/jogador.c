#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // biblioteca que permite o uso do 'getch()'
#include <locale.h> //biblioteca que permite o uso do 'setlocale()'
#include <windows.h> //biblioteca que permite o uso do "Sleep()"
#include <unistd.h> //biblioteca que permite o uso do "usleep()" dos creditos
#include "deck.h"




void imprimirEfeito(char *txt , int intervalo){ 

// Botei esse efeito para ficar mais apresentavel. Quando quiser uma frase com um efeito, bota essa funcaoo com o parametro do intervalo
				
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
	strcpy(p->nome , "Saphira");//declarando o nome do personagem como Saphira através da funcao "strcpy"
	p->vida += 15; //beneficio do personagem
}


void grimgar(personagem *p){
	strcpy(p->nome , "Grimgar");//declarando o nome do personagem como Saphira através da funcao "strcpy"
	p->energia ++; //beneficio do personagem
}



void Iniciar(personagem *p){
	int aux;
	//Funcao para o inicio do jogo

	system("cls"); // limpa o terminal
	imprimirEfeito("Esses sao os personagens do jogo!!" , 38);
	printf("\n");
	imprimirEfeito("Saphira, fada da lua - Uma fada da lua misteriosa, protetora dos segredos noturnos e imagem de magia noturna e tranquilidade na floresta encantada. Poder de curandeira: Comece com mais 15 pontos de Vida\n\n" , 38);
	imprimirEfeito("Grimgar, cavaleiro abissal - Um cavaleiro abissal e habilidoso, vestido com uma armadura negra e um elmo com chifres, cujo passado misterioso o torna temido e respeitado. Investida feroz: Adquira mais 1 ponto de energia\n\n" , 38);

	imprimirEfeito("Escolha seu personagem!!!\n" , 38);
	printf("1 - Saphira\n");
	printf("2 - Grimgar\n");


	scanf("%d",&aux);
	inicializa_personagem(p); // funcao criada para inicializar o personagem com os valores padroes de vida e energia

	switch (aux)//switch para chamar as funcoes de acordo com a escolha do usuario
	{
		case 1:
			saphira(p);//chama a funcao que declara o nome do personagem
			imprimePersonagem(p);
			break;
		case 2:
			grimgar(p);//chama a funcao que declara o nome do personagem
			imprimePersonagem(p);
			break;

		default:
			printf("[ERROR]");
			break;
	}
		
}


void creditos(){

	system("cls");//limpa o terminal
	
	printf("Professor Orientador:\nMarcio Soussa\n");
	printf("\nAlunos:\n");
	printf("\nBeatriz Rosa\nDavi Passos\nMaria Luiza Queiroz\nMateus Jatoba\n");

	Sleep(1500);

	printf("\nAperte <ENTER> para ver nosso patrocinador");

	int tecla = getch();//le a tecla
	
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
	int teclaMenu; //variaveis
	char nome_jogador[10];//variaveis

	personagem p; //personagem
	
	
	imprimirEfeito("Bem - Vindo ao Nosso Jogo !!!\n" , 38);
	printf("Insira seu nome: ");
	scanf("%s" , nome_jogador);
	
	system("cls");
	
	printf("\nOi, %s. Vamos jogar!!!\n" , nome_jogador);
	Sleep(500);
	imprimirEfeito("Pressione uma tecla a sua escolha:\n" , 38);
	Sleep(500);
	printf("<ENTER> para Iniciar \n<ESC> para os creditos \n") ;//opcoes do menu
	
	teclaMenu = getch();//resgata a tecla 	
	
	
	if(teclaMenu == 13){
		Iniciar(&p); //chamada do inicio do jogo
	}

	if(teclaMenu == 27){
		creditos();//chamada do creditos
	}		
} 