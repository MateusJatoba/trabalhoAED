#ifndef COMBATE_H
#define COMBATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define TAMANHO_MAX 100
#define TAMANHO_FILA 10

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
        printf("Tipo: %d\n", atu->info.tipo);
        printf("Valor: %d\n", atu->info.valor);
        printf("Custo: %d\n", atu->info.custo);
        printf("\n");

        atu = atu->prox;
    }
}

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