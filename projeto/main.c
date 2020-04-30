#include "interface.h"
#include "dados.h"
#include <stdio.h>

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
