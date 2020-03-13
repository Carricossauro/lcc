#include "dados.h"
#include <stdlib.h>

ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e->jogador_atual = 1;
    e->num_jogadas = 0;
    for (int linha = 0; linha < 8; linha++){
        for (int coluna = 0; coluna < 8; coluna++){
            e->tab[coluna][linha] = VAZIO;
        }
    }
    e->tab[3][4] = BRANCA;
    e->ultima_jogada.coluna = 4;
    e->ultima_jogada.linha = 3;
    return e;
}

int obter_jogador_atual(ESTADO *e) {
    return e->jogador_atual;
}

int obter_numero_de_jogadas(ESTADO *e) {
    return e->num_jogadas;
}

int obter_estado_casa(ESTADO *e, COORDENADA c) {
    int coluna = c.coluna;
    int linha = c.linha;
    int r = 0;
    if (e->tab[linha][coluna] == VAZIO)
        r = 1;
    return r;
}