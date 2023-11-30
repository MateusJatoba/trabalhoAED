#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h> // biblioteca que permite o uso do 'getch()'
#include <locale.h> //biblioteca que permite o uso do 'setlocale()'
#include <windows.h> //biblioteca que permite o uso do "Sleep()"
#include <unistd.h> //biblioteca que permite o uso do "usleep()" dos creditos
#include "JOGO_BETA.h"

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

void popularMonstro(tp_monstro *m){
    if(m->monster_id == 1){//Monstro 1 tem nome de JEFF
        m->vida = 50; // declarando a vida do monstro
        m->moveset = 1;
        m->defesa = 0;
    }

    else if (m->monster_id == 2)//monstro 2 tem nome de JHONNY
    {
        m->vida = 50;//declarando a vida
        m->moveset = 2;
    }
}

void mostrarMonstro(tp_monstro *m){
    if(m->monster_id == 1){
        printf("JEFF -- INIMIGO");
        printf("\nVIDA %d", m->vida);
    }

    else if (m->monster_id == 2)//monstro 2 tem nome de JHONNY
    {
        printf("JHONNY -- INIMIGO\n");
        printf("VIDA: %d" , m->vida);
    }
}

void status_Player(personagem *p, tp_mao *mao){ // função para mostrar a vida do personagem, energia e cartas
    p->energia = 4;
    printf("\n\n-----------------------\n");

    
    imprimePersonagem(p);
    printf("\n---------------------------------CARTAS---------------------------------\n");

    printf("\n\nLegenda das cartas:\n[Tipo 1] - Ataque\n[Tipo 2] - Defesa\n");

    printf("\n-----------------------\n");
    imprime_mao(mao);
}

void popula_fila(tp_fila *movfila, tp_fila *valfila) {
    inicializar_fila(movfila);
    inicializar_fila(valfila);

    enfileirar(movfila, 'a');
    enfileirar(movfila, 'd');
    enfileirar(movfila, 'e');

    enfileirar(valfila, 6);
    enfileirar(valfila, 8);
    enfileirar(valfila, 3);
}

void enfileirar_no_final(tp_fila *fila, int valor) {
    if (fila->tras == MAX - 1)
        fila->tras = -1;
    
    fila->tras++;
    fila->elementos[fila->tras] = valor;
}

void mostrarAcao(tp_monstro *m, tp_fila *movfila, tp_fila *valfila, int *mov, int *val) {
    int movSelect;
    int ValSelect;

    movSelect = desenfileirar(movfila);
    ValSelect = desenfileirar(valfila);

    enfileirar_no_final(valfila, ValSelect);
    enfileirar_no_final(movfila, movSelect);

    switch (movSelect) {
        case 'a':
            mostrarMonstro(m);
            printf("\nVai Atacar = %d", ValSelect);
            break;
        case 'd':
            mostrarMonstro(m);
            printf("\nVai Defender = %d", ValSelect);
            break;
        case 'e':
            mostrarMonstro(m);
            printf("\nVai se Curar = %d", ValSelect);
            break;
        default:
            break;
    }

    *mov = movSelect;
    *val = ValSelect;
}

void jogar_carta(personagem *p, int carta_id, tp_monstro *m){
    int atq;
    switch (carta_id)
    // ataque = diminuir a vida do monstro
    // defesa =  diminuir o ataque do monstro
    {
    case 1: // atq
        if(m->defesa > 0){
            m->defesa = m->defesa - 3;
            if(m->defesa < 0){
                atq = m->defesa * -1;
                m ->vida = m->vida - atq;
                p->energia -= 1;  
            }
        }
        else{
            m ->vida = m->vida - 3;
            p->energia -= 1;    
        }
        
        break;
    case 2: // atq
        if(m->defesa > 0){
            m->defesa = m->defesa - 5;
            if(m->defesa < 0){
                atq = m->defesa * -1;
                m ->vida = m->vida - atq;
                p->energia -= 2;  
            }
        }
        else{
            m ->vida = m->vida - 5;
            p->energia -= 2;    
        }
        break;
    case 3: // atq
        if(m->defesa > 0){
            m->defesa = m->defesa - 4;
            if(m->defesa < 0){
                atq = m->defesa * -1;
                m ->vida = m->vida - atq;
                p->energia -= 1;  
            }
        }
        else{
            m ->vida = m->vida - 4;
            p->energia -= 1;    
        }
        break;
    case 4: // atq
        if(m->defesa > 0){
            m->defesa = m->defesa - 6;
            if(m->defesa < 0){
                atq = m->defesa * -1;
                m ->vida = m->vida - atq;
                p->energia -= 3;  
            }
        }
        else{
            m ->vida = m->vida - 6;
            p->energia -= 3;    
        }
        break;
    case 5: // def
        p->defesa +=  3;
        p->energia -= 2;
        break;
    case 6: // def
        p->defesa += 2;
        p->energia -= 1;
        break;
    case 7: // def
        p->defesa += 7;
        p->energia -= 3;
        break;
    case 8: // def
        p->defesa += 9;
        p->energia -= 4;
        break;
    
    default:
        break;
    }

    m->defesa = 0;
}

void selecionador_cartas(personagem *p, tp_mao **mao, tp_monstro *m){
    int select, remove_sucesso;
    p ->energia = 4;
    while (p->energia > 0) {  // Corrigi o operador de comparação
        printf("\n(para terminar a rodada digite 0)\n");
        printf("\nSelecione uma carta por id: ");
        scanf("%d", &select);
        remove_sucesso = remove_cartaid(mao, select);
        if(select == 0){
            p->energia = 0;
        }
        else{
            if (remove_sucesso == 1) {  // Corrigi a chamada da função
                printf("\nCARTA %d SELECIONADA!\n",select);
                jogar_carta(p,select,m); 
                printf("\nRESTAM :%d PONTOS DE ENERGIA\n",p->energia);
            }
            else {
                printf("\nSELECIONE OUTRA CARTA\n");
            }    
        }
    }
}

void ataque_monstro(personagem *p, tp_monstro *m, int movfila, int valfila) {
    int atq;
    switch (movfila) {
    case 'a':
        if (p->defesa > 0) { // primeiro termina a defesa e oque sobra afeta a vida
            p->defesa = p->defesa - valfila;
            if (p->defesa < 0) {
                atq = p->defesa * -1;
                m->vida = m->vida - atq;
            }
        } 
        else {
            p->vida = p->vida - valfila;
        }
        break;
    case 'd':
        m->defesa = valfila;
        break;
    case 'e':
        break;
    default:
        break;
    }
    p->defesa = 0;
}

void rodadas(tp_carta e, personagem *p, tp_mao *mao, tp_monstro *m, tp_fila *movfila, tp_fila *valfila) {
    int mov;
    int val;
    popularMonstro(m);
    int i = 0;
    popula_fila(movfila, valfila);

    while (p->vida > 0 && m->vida > 0) {

        cava(&mao, e);
        
        printf("\n--------------RODADA %d--------------\n\n", (i + 1));
        mostrarAcao(m, movfila, valfila, &mov, &val);
        status_Player(p, mao);
        selecionador_cartas(p, &mao, m);
        ataque_monstro(p, m, mov, val);
        
        printf("\nFIM DE RODADA\n");
        Sleep(1000);  // Adiciona uma pausa de 2 segundos para melhorar a experiência visual
        system("cls");
        i++;
    }

    system("pause");  // Pausa a execução para visualização dos resultados
}

void criar_jogador(){
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

void combate123() {
    tp_fila valfila; // filas do monstro
    tp_fila movfila;

    gerar_seed();

    tp_deck h; // declarando deck e mão
    tp_carta e;
    inicializa_deck(&h);
    DeclaraDeck(&h);
    embaralha_deck(&h);

    tp_mao mao_jogador;
    tp_mao *mao_jogador_ptr = &mao_jogador;
    inicializa_mao(mao_jogador_ptr);

    personagem p; // personagem
    inicializa_personagem(&p);
    grimgar(&p);

    tp_monstro m;
    m.monster_id = 1;

    // compra as cartas do deck para a mão do jogador
    rodadas(e, &p, mao_jogador_ptr, &m, &movfila, &valfila);
}

void caminho123(){
    tp_listase_cam *lista;
    personagem p;
    inicializa_personagem(&p);
    criar_caminho(&lista , &p);
    imprime_listase(lista);
}

int main(){
    criar_jogador();
    caminho123();
    // combate123();
}
