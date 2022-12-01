/**
@file main.c
Definição do estado e das funções que o manipulam
*/

/** Dependências */
#include "interface.h"
#include "dados.h"
#include <stdio.h>

/**
\brief Função que inicia o jogo
@returns 0 se não houver erros
*/
int main() {
    ESTADO *e = inicializar_estado();
    int r;
    while (interpretador(e)) {
        if ((r = gameOver(e, obter_ultima_jogada(e)))) {
            printf("O vencedor é o jogador %d.", r);
            break;
        }
    }
    return 0;
}
