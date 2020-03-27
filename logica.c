#include "logica.h"
#include "dados.h"

int jogar(ESTADO *e, COORDENADA c)
{
    if(casa_esta_livre(e, c))
    {
        mudar_casa(e, c);
        muda_jogador(e);
        add_jogada(e);
        return 1;
    }
    else
        return 0;
}

int gameOver(ESTADO *e, COORDENADA c) {
    COORDENADA co;
    if (c.linha == 0 && c.coluna == 7) return 2;
    if (c.linha == 7 && c.coluna == 0) return 1;

    int lin = obter_linha(c), col = obter_coluna(c);
    for (int i = lin - 1; i <= lin + 1; i++) {
        for (int k = col - 1; k <= col + 1; k++) {
            co = cria_coordenada(i,k);
            if (casa_esta_livre(e, co)) return 0;
        }
    }
    return (obter_jogador_atual(e) == 1 ? 2 : 1);
}
