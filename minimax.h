#ifndef PROJETO_LA_MINIMAX_H
#define PROJETO_LA_MINIMAX_H

#include "dados.h"
#include "logica.h"

/**
\brief Definição da estrutura da árvore
*/
typedef struct Tree{
    COORDENADA nodo;
    COORDENADA *proximo[8];
}*arvore;

/**
\brief Função que inicializa uma árvore
@param e Apontador para o estado do jogo
@param c coordenada da última jogada
@return árvore das jogadas
*/
arvore inicializa_arvore(ESTADO *e, COORDENADA c, int jog);

/**
\brief Função que implementa o algoritmo minimax
@param altura altura da árvore
@param c coordenada da última jogada
@param e apontador para o estado de jogo
@return valor da jogada
*/
float Minimax(int altura, COORDENADA c, ESTADO *e, int jog);

/**
\brief Função que determina o valor de uma jogada
@param c coordenada da última jogada
@param e apontador para o estdo de jogo
@param altura altura da árvore
@param jogador jogador 1 ou 2
@return
*/
float valor_jogada(COORDENADA c, ESTADO *e, int altura, int jogador);

#endif //PROJETO_LA_MINIMAX_H
