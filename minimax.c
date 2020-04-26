#include "minimax.h"
#include "logica.h"
#include "dados.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

arvore inicializa_arvore(ESTADO *e, COORDENADA c, int jog)
{
    arvore tree = malloc(sizeof(struct Tree));
    tree->nodo = c;
    COORDENADA *c1;
    int a = 0;
    if (jog == 1) {
        for (int i = c.linha - 1; i <= c.linha + 1 ; i++)
        {
            for (int j = c.coluna - 1; j <= c.coluna + 1; j++)
            {
                c1 = malloc(sizeof(COORDENADA));
                c1->linha = i;
                c1->coluna = j;

                if(c1->linha != c.linha || c1->coluna != c.coluna)
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
    }
    else {
        for (int i = c.linha + 1; i >= c.linha - 1 ; i--)
        {
            for (int j = c.coluna + 1; j >= c.coluna - 1; j--)
            {
                c1 = malloc(sizeof(COORDENADA));
                c1->linha = i;
                c1->coluna = j;

                if(c1->linha != c.linha || c1->coluna != c.coluna)
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
    }
    return tree;
}


float Minimax(int altura, COORDENADA c, ESTADO *e, int jog)
{
    float k = -INT_MIN;
    float valor;
    if (jogar(e, c)) {
        arvore tree = inicializa_arvore(e, c, jog);

        if(altura == 0 || gameOver(e, c))
            k = valor_jogada(c, e, altura, jog);
        else {

            for (int i = 0; i < 8; i++)
            {
                if(tree->proximo[i] != NULL)
                {
                    valor = Minimax(altura - 1, *tree->proximo[i], e, (jog == 1) ? 2 : 1);
                    if(valor > k)
                    {
                        k = valor;
                    }
                }
            }
        }
        retirar_ultima_jogada(e);
    }
    return k;
}

float valor_jogada(COORDENADA c, ESTADO *e, int altura, int jogador){
    float a = 1;
    int x = gameOver(e,c);
    if (x != 0) {
        if(x == jog)
            a = 100;
        else if (x != jog)
            a = -100;
    }
    return a;
}