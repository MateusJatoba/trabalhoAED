#include <stdio.h>
#include <stdlib.h>
#include "JOGO_BETA.h"

int main(){
    tp_deck dck;
    char nome[] = {"teste.txt"};
    inicializa_deck(&dck);
    DeclaraDeck(&dck);
    gravar_disco(nome , &dck);
}