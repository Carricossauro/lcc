/**
@file interface.h
Definição das funçôes que fornecem a ligação ao jogador
*/
#ifndef PROJETO_LA_INTERFACE_H
#define PROJETO_LA_INTERFACE_H
#include "dados.h"
#include "logica.h"
#include <stdlib.h>
#include <bits/types/FILE.h>


/**
\brief Função que mostra o tabuleiro na linha de comandos
@param e Apontador para o estado do jogo
@param jogo File stream para o output
*/
void mostrar_tabuleiro(ESTADO e, FILE *jogo);

/**
\brief Função que recebe o input do utilizador
@param e Apontador para o estado do jogo
*/
int interpretador(ESTADO *e);

/**
\brief Função que imprime o prompt
@param e Apontador para o estado do jogo
*/
void mostrar_prompt(ESTADO *e);

/**
/brief Função que lê um ficheiro
@param ficheiro ficheiro
@param e Apontador para o Estado do jogo
*/
void ler (char *ficheiro, ESTADO *e);

/**
/brief Função que grava um ficheiro
@param ficheiro ficheiro
@param e Apontador para o Estado do jogo
*/
void gravar (char *ficheiro, ESTADO *e);

/**
/brief Função que mostra os movimentos
@param jogo File stream para o output
@param e Apontador para o Estado do jogo
*/
void movs (FILE *jogo, Estado *e);
#endif //PROJETO_LA_INTERFACE_H
