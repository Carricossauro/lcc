/**
@file interface.h
Definição das funçôes que fornecem a ligação ao jogador
*/
#ifndef PROJETO_LA_INTERFACE_H
#define PROJETO_LA_INTERFACE_H
#include "dados.h"
#include "logica.h"

/**
\brief Função que mostra o tabuleiro na linha de comandos
@param e Apontador para o estado do jogo
*/
void mostrar_tabuleiro(ESTADO e);

/**
\brief Função que recebe o input do utilizador
@param e Apontador para o estado do jogo
*/
int interpretador(ESTADO *e);
#endif //PROJETO_LA_INTERFACE_H
