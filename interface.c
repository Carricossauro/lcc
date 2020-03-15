#include "dados.h"
#include "logica.h"
#include <stdio.h>
#include <string.h>
#define BUF_SIZE 1024

void mostrar_tabuleiro(ESTADO *e) {
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {
            if (i == 0 && k == 7)
                printf("2");
            else if (i == 7 && k == 0)
                printf("1");
            else
                printf((obter_casa(e, k, i) == VAZIO) ? "." : (obter_casa(e, i, k) == BRANCA) ? "*" : "#" );
        }
        putchar('\n');
    }
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];

    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;

    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        jogar(e, coord);
        mostrar_tabuleiro(e);
    }
    return 1;
}