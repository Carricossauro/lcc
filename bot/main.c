#include "bot.h"

int main(int argc, char **argv) {

    if(argc == 3){

        ESTADO *e = inicializar_estado();
        ler(argv[1], e);
        jog2(e);
        muda_inc(e, obter_jogador_atual(e));
        gravar(argv[2], e);
    }
}
