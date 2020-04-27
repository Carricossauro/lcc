#ifndef PROJETO_LA_MINIMAX_H
#define PROJETO_LA_MINIMAX_H

#include "dados.h"
#include "logica.h"

/**
\brief Definição da estrutura da árvore
*/
typedef struct Tree{
    /** Coordenada de uma jogada */
    COORDENADA nodo;
    /** Coordenadas vizinhas */
    COORDENADA *proximo[8];
}*arvore;

/**
\brief Função que inicializa uma lista
@param e Apontador para o estado do jogo
@param c Coordenada da última jogada
@return Lista das jogadas
*/
arvore inicializa_arvore(ESTADO *e, COORDENADA c, int jog);

/**
\brief Função que implementa o algoritmo minimax
@param altura Comprimemto  da lista
@param c Coordenada da última jogada
@param e Apontador para o estado de jogo
@returns Valor da jogada
*/
float Minimax(int altura, COORDENADA c, ESTADO *e, int jog);

/**
\brief Função que determina o valor de uma jogada
@param c Coordenada da última jogada
@param e Apontador para o estado de jogo
@param altura Comprimento da lista
@param jogador Jogador 1 ou 2
@returns valor que uma jogada tem
*/
float valor_jogada(COORDENADA c, ESTADO *e, int altura, int jogador);

#endif //PROJETO_LA_MINIMAX_H
