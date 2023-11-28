
#ifndef LISTASE_H
#define LISTASE_H
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "deckcaminho.h"

typedef int
	tp_item;

typedef struct tp_no{
	tp_item info;
	struct tp_no *prox;
}tp_listase;

tp_listase * inicializa_listase(){ // atribui NULL ao 1o no da Lista SE // em código: lista = inicializa_listase
		return NULL;
}

int listase_vazia(tp_listase *lista){
	if(lista==NULL) return 1;
	return 0;
}

tp_listase * aloca_listase(){ // ela ira alocar um espaco na memoria
	tp_listase *novo_no;
	novo_no = (tp_listase*) malloc(sizeof(tp_listase));
	return novo_no;
}

int insere_listase_no_fim(tp_listase **l, tp_item e){ // no codigo: insere...(lista, 10...)
	tp_listase *novo_no, *atu;
	novo_no = aloca_listase(); // aqui esta pegando o novo no e apontando para o NULL
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

void imprime_listase(tp_listase *lista){
	tp_listase *atu;
	atu = lista;
	while(atu != NULL){
		printf("%c ", atu->info);
		atu = atu->prox;
	}
}

int remove_listase(tp_listase **lista, tp_item e){
	tp_listase *ant, *atu;
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

tp_listase *busca_listase(tp_listase *lista, tp_item e){
	tp_listase *atu;
	atu = lista;
	while((atu != NULL) && (atu->info != e)){
		atu = atu->prox;
	}
	if(atu == NULL) return NULL;
	return atu;
}

int tamanho_listase(tp_listase *lista){
	int cont = 0;
	tp_listase *atu;
	atu = lista;
	while(atu != NULL){
		cont++;
		atu = atu->prox;
	}
	return cont;
}

void destroi_listase(tp_listase **l){
	tp_listase *atu;
	atu = *l;
	while(atu != NULL){
		*l = atu->prox;
		free(atu);
		atu = *l;
	}
	*l = NULL;

}
int listase_igual(tp_listase *l1, tp_listase *l2){
	tp_listase *atu1, *atu2;
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
			minha_carta.valor[0] += 2;
			printf("Valor adcionado!!: %d\n\n" , minha_carta.valor[0]);
			break;
		
		case 2:
			minha_carta.valor[1] += 2;
			printf("Valor adcionado!!: %d\n\n", minha_carta.valor[1]);
			break;
		
		case 3:
			minha_carta.valor[2] += 2;
			printf("Valor adcionado!!: %d\n\n" , minha_carta.valor[2]);
			break;
		default:
			break;
		}
	}
	
	

}

void combate(){
    printf("\nChamada do combate\n\n");
}

void combate_boss(){
    printf("\nChamada do combate do chefe\n");
}

void criar_caminho(tp_listase **lista , personagem *p){ //funcao para a criacao do caminho
    char aux;
    *lista = inicializa_listase(); //caminho eh uma listase
    insere_listase_no_fim(lista, 'C'); // definindo o primeiro passo do caminho - combate obrigatorio
    
    combate();

    printf("Defina seu proximo passo:\n[D] - Descanso\n[C] - Combate\n"); 
    scanf(" %c", &aux); // opcao de escolha, descanso ou outro combate
    aux = tolower(aux); //controle de erro do usuario
    
    if (aux == 'd') //caminho com o descanso
    {
        insere_listase_no_fim(lista , 'D');

        descanso(p) ;

        insere_listase_no_fim(lista , 'C');

        combate();
        printf("Defina seu proximo passo:\n[D] - Descanso\n[C] - Combate\n"); 
        scanf(" %c", &aux); // opcao de escolha, descanso ou outro combate
        aux = tolower(aux); //controle de erro do usuario

        if (aux == 'd')
        {
            insere_listase_no_fim(lista , 'D');
            descanso(p);
            insere_listase_no_fim(lista , 'B');
            combate_boss();
        }

        else{
            insere_listase_no_fim(lista , 'C');
            combate();

            insere_listase_no_fim(lista , 'B');
            combate_boss();
        }
        
        
    }
    
    else{ //caminho sem o descanso

        
        insere_listase_no_fim(lista , 'C');
        combate();
        insere_listase_no_fim(lista , 'C');
        combate();
        
        printf("Defina seu proximo passo:\n[D] - Descanso\n[C] - Combate\n"); 
        scanf(" %c", &aux); // opcao de escolha, descanso ou outro combate
        aux = tolower(aux); //controle de erro do usuario

        if (aux == 'd')
        {
            insere_listase_no_fim(lista , 'D');
            descanso(p);
            insere_listase_no_fim(lista , 'B');
            combate_boss();
        }

        else{
            insere_listase_no_fim(lista , 'C');
            combate();

            insere_listase_no_fim(lista , 'B');
            combate_boss();
        }
    }

    
}


#endif
