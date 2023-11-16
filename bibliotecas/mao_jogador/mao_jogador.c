#include <stdio.h>
#include <stdlib.h>
#include "embaralhadeck_maojogador.h"
#include "maojogador.h"


int main() {
    tp_deck h;
    tp_carta e;
    inicializa_deck(&h);
    DeclaraDeck(&h);
    embaralha_deck(&h);
    

    tp_mao mao_jogador;
    tp_mao *mao_jogador_ptr = &mao_jogador;
    inicializa_mao(mao_jogador_ptr);

    // Adicione cartas à mão do jogador e imprima a mão
    cava(&mao_jogador_ptr, e);
    imprime_mao(mao_jogador_ptr);

   
    return 0;
}