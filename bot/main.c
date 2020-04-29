#include <stdio.h>
#include "bot.h"

int main(int argc, char **argv) {

    if(argc == 3){

        ESTADO *e = inicializar_estado();
        ler(argv[1], e);
        mostrar_tabuleiro(e, stdout);
        movs(stdout, e);
    }
}
