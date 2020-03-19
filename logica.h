/**
@file logica.h
Definição das funções que representam a jogabilidade
*/
#ifndef PROJETO_LA_LOGICA_H
#define PROJETO_LA_LOGICA_H

#include "dados.h"

/**
\brief Função que recebe uma coordenada e joga quando é válida
@param e Apontador para o estado do jogo
@param c Coordenada da jogada
@returns 1 - Jogada Válida \n 0 - Jogada Inválida
*/
int jogar(ESTADO *e, COORDENADA c);

/**
\brief Função que determina se o jogo foi ganho
@param e Apontado para o estado do jogo
@param c Coordenada da última jogada
@returns 0 - Jogo não acabou \n 1 - Vitória do jogador 1 \n 2 - Vitória do jogador 2
*/
int gameOver(ESTADO *e, COORDENADA c);

#endif //PROJETO_LA_LOGICA_H