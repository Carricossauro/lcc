#include "minimax.h"
#include "logica.h"
#include "dados.h"
#include <stdio.h>
#include <stdlib.h>

arvore inicializa_arvore(ESTADO *e, COORDENADA c)
{
    arvore tree = malloc(sizeof(struct Tree));
    tree->nodo = c;
    COORDENADA *c1;
    int a = 0;

    for (int i = c.linha - 1; i < c.linha + 1 ; i++)
    {
        for (int j = c.coluna - 1; j < c.coluna; j++)
        {
            c1 = malloc(sizeof(COORDENADA));
            c1->linha = i;
            c1->coluna = j;

            if(c1->linha != c.linha && c1->coluna != c.coluna)
            {
                if(casa_esta_livre(e, *c1))
                {
                    tree->proximo[a] = c1;
                    a++;
                }
                else
                {
                    tree->proximo[a] = NULL;
                    a++;
                    free(c1);
                }
            }
            else
            {
                free(c1);
            }
        }
    }
    return tree;
}


int minimax(int altura, COORDENADA c, ESTADO *e)
{
    int j = obter_jogador_atual(e);
    int k;
    int valor;

    arvore tree = inicializa_arvore(e, c);

    if(altura == 0 || gameOver(e, c))
        return valor_jogada(e, c);


    k = -9999;

    for (int i = 0; i < 8; i++)
    {
        if(tree->proximo[i] != NULL)
        {
            jogar(e, c);
            valor = Minimax(altura - 1, *tree->proximo[i], e);
            retirar_ultima_jogada(e);

            if(valor > k)
            {
                k = valor;
            }
        }
    }
    return k;
}

int valor_jogada(COORDENADA c, ESTADO *e){

    if(gameOver(e, c) == obter_jogador_atual(e)) {
        return 1000;
    }else if (gameOver(e, c) != obter_jogador_atual(e)) {
        return -1000;
    }else if (gameOver(e, c) == 0)
        return distancia(c, origem);
}