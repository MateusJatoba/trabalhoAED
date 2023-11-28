#include <stdio.h>
#include <stdlib.h>
#include "caminho.h"

int main(){
    tp_listase *lista;
    personagem p;
    

    inicializa_personagem(&p);

    criar_caminho(&lista , &p);
    imprime_listase(lista);

   
}