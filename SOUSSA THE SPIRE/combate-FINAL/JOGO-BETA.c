#ifndef JOGO_BETA_H
#define JOGO_BETA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h> // biblioteca que permite o uso do 'getch()'
#include <locale.h> //biblioteca que permite o uso do 'setlocale()'
#include <windows.h> //biblioteca que permite o uso do "Sleep()"
#include <unistd.h>

#define MAX 100
#define TAMANHO_MAX 100
#define TAMANHO_FILA 10

int numero_combate = 1;
int qnt_cartas_jogadas = 0;

// MAO.h --------------------------------------------------------------------------------

typedef struct {
    int carta_id;
    int tipo;
    int valor;
    int custo;
} tp_carta;

typedef struct tp_no {
    tp_carta info;
    struct tp_no *prox;
} tp_mao;

tp_mao *inicializa_mao() {
    return NULL;
}

int mao_vazia(tp_mao *mao_jogador) {
    if (mao_jogador == NULL)
        return 1;
    return 0;
}

tp_mao *aloca_listase() {
    tp_mao *novo_no;
    novo_no = (tp_mao *)malloc(sizeof(tp_mao));
    return novo_no;
}

int insere_mao_no_fim(tp_mao **l, tp_carta e) {
    tp_mao *novo_no, *atu;
    novo_no = aloca_listase();
    if (novo_no == NULL)
        return 0;

    novo_no->info = e;
    novo_no->prox = NULL;

    if (mao_vazia(*l)) {
        *l = novo_no;
    } else {
        atu = *l;
        while (atu->prox != NULL) {
            atu = atu->prox;
        }
        atu->prox = novo_no;
    }
    return 1;
}

int remove_cartaid(tp_mao **mao_jogador, int carta_id) {
    tp_mao *ant, *atu;
    atu = *mao_jogador;
    ant = NULL;

    while ((atu != NULL) && (atu->info.carta_id != carta_id)) {
        ant = atu;
        atu = atu->prox;
    }

    if (atu == NULL)
        return 0;

    if (ant == NULL) {
        *mao_jogador = atu->prox;
    } else {
        ant->prox = atu->prox;
    }

    free(atu);
    atu = NULL;

    return 1;
}

int remove_mao(tp_mao **mao_jogador, tp_carta e) {
    tp_mao *ant, *atu;
    atu = *mao_jogador;
    ant = NULL;

    while ((atu != NULL) && (atu->info.carta_id != e.carta_id)) {
        ant = atu;
        atu = atu->prox;
    }

    if (atu == NULL)
        return 0;

    if (ant == NULL) {
        *mao_jogador = atu->prox;
    } else {
        ant->prox = atu->prox;
    }

    free(atu);
    atu = NULL;
    return 1;
}

int tamanho_mao(tp_mao *mao_jogador) {
    int cont = 0;
    tp_mao *atu;
    atu = mao_jogador;
    while (atu != NULL) {
        cont++;
        atu = atu->prox;
    }
    return cont;
}

void destroi_mao(tp_mao **m) {
    tp_mao *atu;
    atu = *m;
    while (atu != NULL) {
        *m = atu->prox;
        free(atu);
        atu = *m;
    }
}

void imprime_mao(tp_mao *mao_jogador) {
    tp_mao *atu = mao_jogador;

    while (atu != NULL) {
        printf("Carta ID: %d\n", atu->info.carta_id);

        switch (atu->info.tipo)
        {
        case 1:
            printf("Tipo: ATAQUE\n");
            break;
        case 2:
            printf("Tipo: DEFESA\n");
            break;
        
        default:
            break;
        }

        printf("Valor: %d\n", atu->info.valor);
        printf("Custo: %d\n", atu->info.custo);
        printf("\n");

        atu = atu->prox;
    }
}

// fila.h --------------------------------------------------------------------------------------

typedef struct {
    int elementos[TAMANHO_FILA];
    int frente;
    int tras;
} tp_fila;

void inicializar_fila(tp_fila *fila) {
    fila->frente = -1;
    fila->tras = -1;
}

int estaVazia(tp_fila *fila) {
    return (fila->frente == -1);
}

int estaCheia(tp_fila *fila) {
    return ((fila->frente == 0 && fila->tras == TAMANHO_FILA - 1) || (fila->frente == (fila->tras + 1) % TAMANHO_FILA));
}

void enfileirar(tp_fila *fila, int valor) {
    if (estaCheia(fila)) {
        printf("Erro: A fila está cheia.\n");
        return;
    }

    if (fila->frente == -1) {
        fila->frente = 0;
    }

    fila->tras = (fila->tras + 1) % TAMANHO_FILA;
    fila->elementos[fila->tras] = valor;
}

int desenfileirar(tp_fila *fila) {
    if (estaVazia(fila)) {
        printf("Erro: A fila está vazia.\n");
        exit(1);
    }

    int valor = fila->elementos[fila->frente];
    if (fila->frente == fila->tras) {
        fila->frente = -1;
        fila->tras = -1;
    } else {
        fila->frente = (fila->frente + 1) % TAMANHO_FILA;
    }

    return valor;
}

// PERSONGAEM.h --------------------------------------------------------------------------------

typedef struct {
    char nome[10];
    int vida;
    int energia;
    int deckPrincipal[5];
    int defesa;
} personagem;

void grimgar(personagem *p) {
    strcpy(p->nome, "Grimgar");
    p->energia++;
}

void inicializa_personagem(personagem *p) {
    p->vida = 20;
    p->energia = 3;
}

void imprimePersonagem(personagem *p) {
    printf("\n%s -- JOGADOR\n", p->nome);
    printf("Pontos de vida: %d\n", p->vida);
    printf("Pontos de energia: %d\n", p->energia);
}

typedef struct {
    int monster_id;
    int vida;
    int moveset;
    int defesa;
} tp_monstro;

int fim_de_jogo(){
    if(numero_combate != 5){
        printf("\nGAME OVER");
        printf("\nJOGADOR VOCE PERDEU O COMBATE\n");
        Sleep(1000);
        return 0;
    }
    else 
        return 1;
}

// DECK.h --------------------------------------------------------------------------------

typedef struct {
    tp_carta carta[MAX];
    int topo;
} tp_deck;

void inicializa_deck(tp_deck *p) {
    p->topo = -1;
}

int deck_vazio(tp_deck *p) {
    if (p->topo == -1)
        return 1;
    else
        return 0;
}

int deck_cheio(tp_deck *p) {
    if (p->topo >= MAX)
        return 1;
    else
        return 0;
}

int push(tp_carta e, tp_deck *p) {
    if (p->topo + 1 <= MAX) {
        (p->topo)++;
        p->carta[p->topo] = e;
        return 1;
    } else
        return 0;
}

int pop(tp_carta *e, tp_deck *p) {
    if ((p->topo) < 0)
        return 0;
    else {
        *e = p->carta[p->topo];
        (p->topo)--;
        return 1;
    }
}

int top(tp_carta *e, tp_deck *p) {
    if ((p->topo) < 0)
        return 0;
    else {
        *e = p->carta[p->topo];
        return 1;
    }
}

int altura_deck(tp_deck *p) {
    return p->topo + 1;
}

void empilha_deck(tp_deck *p, tp_deck *p2) {
    tp_deck aux;
    tp_carta e;

    inicializa_deck(&aux);

    if (altura_deck(p) + altura_deck(p2) > MAX)
        printf("\n impossivel realizar essa funcao! limite atingido \n");
    else {
        while (!deck_vazio(p2)) {
            pop(&e, p2);
            push(e, &aux);
        }
        while (!deck_vazio(&aux)) {
            pop(&e, &aux);
            push(e, p);
        }
    }
}

void ver_deck(tp_deck *p) {
    tp_carta e;
    tp_deck aux;

    inicializa_deck(&aux);

    while (!deck_vazio(p)) {
        pop(&e, p);
        printf("\n Carta: %i", e.carta_id);
        printf("\n Tipo: %i", e.tipo);
        printf("\n Custo: %i", e.custo);
        printf("\n Valor: %i \n", e.valor);
        push(e, &aux);
    }
    while (!deck_vazio(&aux)) {
        pop(&e, &aux);
        push(e, p);
    }
}

void DeclaraDeck(tp_deck *h) {
    tp_carta c1;
    c1.carta_id = 1;
    c1.valor = 3;
    c1.tipo = 1;
    c1.custo = 1;

    tp_carta c2;
    c2.carta_id = 2;
    c2.valor = 5;
    c2.tipo = 1;
    c2.custo = 2;

    tp_carta c3;
    c3.carta_id = 3;
    c3.valor = 4;
    c3.tipo = 1;
    c3.custo = 1;

    tp_carta c4;
    c4.carta_id = 4;
    c4.valor = 6;
    c4.tipo = 1;
    c4.custo = 3;

    tp_carta c5;
    c5.carta_id = 5;
    c5.valor = 3;
    c5.tipo = 2;
    c5.custo = 2;

    tp_carta c6;
    c6.carta_id = 6;
    c6.valor = 2;
    c6.tipo = 2;
    c6.custo = 1;

    tp_carta c7;
    c7.carta_id = 7;
    c7.valor = 7;
    c7.tipo = 2;
    c7.custo = 3;

    tp_carta c8;
    c8.carta_id = 8;
    c8.valor = 9;
    c8.tipo = 2;
    c8.custo = 4;

    push(c8, h);
    push(c7, h);
    push(c6, h);
    push(c5, h);
    push(c4, h);
    push(c3, h);
    push(c2, h);
    push(c1, h);
}

int random() {
    int r = rand() % 2;
    return r;
}

void gerar_seed() {
    int seed = time(NULL);
    printf("-----------------\nseed :%d\n-----------------\n\n\n", seed);
    srand(seed);
}

void embaralha_deck(tp_deck *h) {
    tp_deck aux1, aux2;
    tp_carta e;
    int x;
    int i;
    inicializa_deck(&aux1);
    inicializa_deck(&aux2);

    for (i = 0; i < 5; i++) {
        while (!deck_vazio(h)) {
            pop(&e, h);
            x = random();
            if (x == 1) {
                push(e, &aux1);
            } else {
                push(e, &aux2);
            }
        }

        empilha_deck(&aux1, &aux2);

        while (!deck_vazio(&aux1)) {
            pop(&e, &aux1);
            push(e, h);
        }
    }
}

void cava(tp_mao **mao_jogador, tp_carta e) {
    int i;
    tp_deck h;
    inicializa_deck(&h);
    DeclaraDeck(&h);
    embaralha_deck(&h);
    *mao_jogador = inicializa_mao();
    for (i = 0; i < 5; i++) {
        pop(&e, &h);
        insere_mao_no_fim(mao_jogador, e);
    }
}

void descarte_deck(tp_mao *mao_jogador, tp_carta e) {
    tp_deck descarte;
    inicializa_deck(&descarte);
    remove_mao(&mao_jogador, e);
    push(e, &descarte);
}

void retorna_deck(tp_deck *descarte, tp_deck *h, tp_carta e) {
    embaralha_deck(descarte);
    while (!deck_vazio(descarte)) {
        pop(&e, descarte);
        push(e, h);
    }
}


#endif

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

// Botei esse efeito para ficar mais apresentável. Quando quiser uma frase com um efeito, bota essa função com o parametro do intervalo
				
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

void Iniciar(){
	//Função para o início do jogo
	setlocale(LC_ALL , "");
	system("cls"); // limpa o terminal
	imprimirEfeito("Esses sao os personagens do jogo!!" , 38);
	printf("\n");
	imprimirEfeito("Grimgar, cavaleiro abissal - Um cavaleiro abissal e habilidoso, vestido com uma armadura negra e um elmo com chifres, cujo passado misterioso o torna temido e respeitado. Investida feroz: Adquira mais 1 ponto de energia\n\n" , 38);
}

void creditos(){

	system("cls");
	
    printf("Creditos: \n");
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
    switch(m->monster_id){
        case 1:
            //"JEFF"
            m->vida = 15;
            m->moveset = 1;
            m->defesa = 0;
            break;
        case 2:
            //"ZUCAN"
            m->vida = 20;
            m->moveset = 2;
            m->defesa = 0;
            break;
        case 3:
            //"GRONIG"
            m->vida = 30;
            m->moveset = 3;
            m->defesa = 0;
            break;
        case 4:
            //"XAMXAM"
            m->vida = 50;
            m->moveset = 4;
            m->defesa = 0;
            break;
        case 5:
            //"JHONNY"
            m->vida = 35;
            m->moveset = 5;
            m->defesa = 0;
            break;
        default:
            break;
    }
}

void mostrarMonstro(tp_monstro *m){
    switch(m->monster_id){
        case 1:
            printf("JEFF -- INIMIGO\n");
            printf("VIDA: %d", m->vida);
            break;
        case 2:
            printf("SAULYN -- INIMIGO\n");
            printf("VIDA: %d", m->vida);
            break;
        case 3:
            printf("GRONIG -- INIMIGO\n");
            printf("VIDA: %d", m->vida);
            break;
        case 4:
            printf("XAMXAM -- INIMIGO\n");
            printf("VIDA: %d", m->vida);
            break;
        case 5:
            printf("ZUCAN -- INIMIGO\n");
            printf("VIDA: %d", m->vida);
            break;
        default:
            break;
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
    enfileirar(movfila, 'a');
    enfileirar(movfila, 'e');

    enfileirar(valfila, 6+numero_combate);
    enfileirar(valfila, 8);
    enfileirar(valfila, 10+numero_combate);
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
                qnt_cartas_jogadas += 1;
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

void checar_vitoria(tp_monstro *m){
    Sleep(300);
    if(m->vida > 0){
        printf("\nGAME OVER");
        printf("\nJOGADOR VOCE PERDEU O COMBATE\n");
        Sleep(1000);
    }

    else if(numero_combate==5){
        printf("\nVOCE VENCEU O CHEFE FINAL!");
        printf("\nBOA BATALHA! AQUI SE ENCERRA SUA JORNADA!\n");
        Sleep(1000);
        creditos();
    }

    else{
        printf("\nVOCE VENCEU");
        printf("\nBOA BATALHA!\n");
        Sleep(1000);
    }
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

    checar_vitoria(m);

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
		printf("1 - Grimgar\n");


		scanf("%d",&aux);
		inicializa_personagem(&p); // funcao criada para inicializar o personagem com os valores padroes de vida e energia

		switch (aux)
		{
			case 1:
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

void combate123(int fase) {
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
    m.monster_id = fase;

    // compra as cartas do deck para a mão do jogador
    rodadas(e, &p, mao_jogador_ptr, &m, &movfila, &valfila);
}

// caminho.h --------------------------------------------------------------------------------

typedef int
	tp_item;

typedef struct tp_no_cam{
	tp_item info;
	struct tp_no_cam *prox;
}tp_listase_cam;

tp_listase_cam * inicializa_listase(){ // atribui NULL ao 1o no da Lista SE // em código: lista = inicializa_listase
		return NULL;
}

int listase_vazia(tp_listase_cam *lista){
	if(lista==NULL) return 1;
	return 0;
}

tp_listase_cam * aloca_listase_cam(){ // ela ira alocar um espaco na memoria
	tp_listase_cam *novo_no;
	novo_no = (tp_listase_cam*) malloc(sizeof(tp_listase_cam));
	return novo_no;
}

int insere_listase_no_fim(tp_listase_cam **l, tp_item e){ // no codigo: insere...(lista, 10...)
	tp_listase_cam *novo_no, *atu;
	novo_no = aloca_listase_cam(); // aqui esta pegando o novo no e apontando para o NULL
	if(novo_no == NULL)
		return 0; // nao aloca memoria
	//atribuir os valores para o novo no:
	novo_no->info = e;
	novo_no->prox = NULL;
	//finaliza o encadeamento do no
	if(listase_vazia(*l)){ // se for o primeiro no, entra aqui
		*l = novo_no;
	}
	
	else {
		atu = *l;
		while(atu->prox != NULL){
			atu = atu->prox; // aponta para o ultimo no
		}
		atu->prox = novo_no;
	}
	return 1;
}

void imprime_listase(tp_listase_cam *lista){
	tp_listase_cam *atu;
	atu = lista;
	while(atu != NULL){
		printf("%c ", atu->info);
		atu = atu->prox;
	}
}

int remove_listase(tp_listase_cam **lista, tp_item e){
	tp_listase_cam *ant, *atu;
	atu = *lista;
	ant = NULL;
	while((atu != NULL) && (atu->info != e)){
		ant = atu;
		atu = atu->prox;
	}
	if(atu == NULL){
		return 0;
	}
	if(ant == NULL){
		*lista = atu->prox;
	}
	else{
		ant->prox = atu->prox;
	}
	free(atu);
	atu = NULL;
	return 1;
}

tp_listase_cam *busca_listase(tp_listase_cam *lista, tp_item e){
	tp_listase_cam *atu;
	atu = lista;
	while((atu != NULL) && (atu->info != e)){
		atu = atu->prox;
	}
	if(atu == NULL) return NULL;
	return atu;
}

int tamanho_listase(tp_listase_cam *lista){
	int cont = 0;
	tp_listase_cam *atu;
	atu = lista;
	while(atu != NULL){
		cont++;
		atu = atu->prox;
	}
	return cont;
}

void destroi_listase(tp_listase_cam **l){
	tp_listase_cam *atu;
	atu = *l;
	while(atu != NULL){
		*l = atu->prox;
		free(atu);
		atu = *l;
	}
	*l = NULL;

}
int listase_igual(tp_listase_cam *l1, tp_listase_cam *l2){
	tp_listase_cam *atu1, *atu2;
	atu1=l1;
	atu2=l2;
	if(tamanho_listase(atu1)!=tamanho_listase(atu2))return 0;
	while(atu1!=NULL){
		if(atu1->info!=atu2->info){
			return 0;
		}
		atu1=atu1->prox;
		atu2=atu2->prox;
		}
		return 1;
}


void descanso(personagem *p){
    int aux = 0;
    printf("O jogador se encontra no espaco de descanso. Escolha uma opcao abaixo:\n[1] - Curar a vida para o valor padrao de 20\n[2] - Melhorar a carta em +2\n");
	scanf("%d" , &aux);

	if (aux == 1)
	{
		inicializa_personagem(p); //restaura o valor de vida padrao
		printf("Valor de vida padrao restaurado!!\n\n");
	}

	if (aux == 2) // faz a adicao no valor das cartas 
	{
		printf("Qual carta deseja melhorar:\n[1] - Ataque\n[2] - Defesa\n[3] - Especial\n");
		scanf("%d" , &aux);
		switch (aux)
		{
		case 1:
			// minha_carta.valor[0] += 2;
			printf("Valor adcionado!!:\n\n");
			break;
		
		case 2:
			// minha_carta.valor[1] += 2;
			printf("Valor adcionado!!:\n\n");
			break;
		
		case 3:
			printf("Valor adcionado!!");
			break;
		default:
			break;
		}
	}
	
}


void combate(){
    combate123(numero_combate);
    printf("\nChamada do combate\n\n");
}

void combate_boss(){
    printf("\nChamada do combate do chefe\n");
}

void imprime_caminho(char vet[5]){
	for (int i = 0; i < 5; i++)
    {
        printf("%c " , vet[i]);
    }
    
}

void criar_caminho(tp_listase_cam **lista , personagem *p){ //funcao para a criacao do caminho
    // inicializa_caminho(&lista);
    // lista = inicializa_listase(); //caminho eh uma listase
    insere_listase_no_fim(lista , 'C'); // definindo o primeiro passo do caminho - combate obrigatorio
    insere_listase_no_fim(lista , 'C');
    insere_listase_no_fim(lista , 'C');
    insere_listase_no_fim(lista , 'D');
    insere_listase_no_fim(lista , 'B');
    tp_listase_cam *atu;
    
    char vet[5];
    atu = *lista;
    int verifica = 0;

    while (atu!=NULL)
    {
        if (atu->info == 'C')
        {
            combate();
            vet[verifica] = 'C';
            verifica ++;
        }

        else if(atu->info == 'D'){
            descanso(p);
            vet[verifica] = 'D';
            verifica ++;
        }
        
        else if(atu->info == 'B'){
            vet[verifica] = 'B';
            combate_boss();
        }

        if (verifica == 1)
        {
            char escolha;
            printf("Desvio a frente!!! Escolha seu proximo movimento:\n[D] - Descanso\n[C] - Combate\n");
            scanf(" %c" , &escolha);
            if (escolha == 'd')
            {   
                tp_listase_cam *desvio;
                desvio = aloca_listase_cam();
                desvio->info = 'D';
                atu = atu->prox;
                desvio->prox = atu->prox;

                atu->prox = desvio;
                vet[verifica] = 'D';
            }
            
        }

        if (verifica == 3)
        {
            char escolha2;
            printf("Desvio a frente!!! Escolha seu proximo movimento:\n[D] - Descanso\n[C] - Combate\n");
            scanf(" %c" , &escolha2);
            if (escolha2 == 'c')
            {   
                tp_listase_cam *desvio2;
                desvio2 = aloca_listase_cam();
                desvio2->info = 'C';
                atu = atu->prox;
                desvio2->prox = atu->prox;

                atu->prox = desvio2;
                vet[verifica] = 'C';
            }
        }
        
        atu = atu->prox;

        
    }

    imprime_caminho(vet);
    
}

void caminho123(){
    tp_listase_cam *lista = NULL;
    personagem p;
    inicializa_personagem(&p);
    criar_caminho(&lista , &p);
    // imprime_caminho(lista);
}

int main(){
   // criar_jogador();
    caminho123();
}