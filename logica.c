//
// Created by pedrusphantom on 3/13/20.
//

#include "logica.h"
#include "dados.h"

int jogar(ESTADO *e, COORDENADA c)
{
    int uLinha = e -> ultima_jogada.linha;
    int uColuna = e -> ultima_jogada.coluna;

    if(obter_estado_casa(e, c))
    {
        e -> tab[uLinha][uColuna] = PRETA;
        e -> tab[c.linha][c.coluna] = BRANCA;

        return 1;
    }
    else
    {
        return 0;
    }
}