#include "listas.h"
/**
@file dados.h
Definição do estado e das funções que o manipulam
*/

#ifndef PROJETO_LA_DADOS_H
#define PROJETO_LA_DADOS_H

/**
\brief Tipo de dados para as casa do tabuleiro
*/
typedef enum {
    /** Casa vazia */ VAZIO,
    /** Casa branca */ BRANCA,
    /** Casa preta */ PRETA} CASA;

/**
\brief Tipo de dados para as coordenadas
*/
typedef struct {
    /** Coluna da coordenada */
    int coluna;
    /** Linha da coordenada */
    int linha;
} COORDENADA;

/**
\brief Tipo de dados para a jogada
*/
typedef struct {
    /** Coordenada do jogador 1 */
    COORDENADA jogador1;
    /** Coordenada do jogador 2 */
    COORDENADA jogador2;
} JOGADA;

/**
\brief Tipo de dados para as jogadas
*/
typedef JOGADA JOGADAS[32];

/**
\brief Tipo de dados para o estado
*/
typedef struct {
    /** Tabuleiro */
    CASA tab[8][8];
    /** Última Jogada */
    COORDENADA ultima_jogada;
    /** Jogadas */
    JOGADAS jogadas;
    /** Número de jogadas */
    int num_jogadas;
    /** Jogador Atual */
    int jogador_atual;
    /** Número de comandos */
    int num_comandos;
    /** Número de movimento*/
    int num_movimento;
    /** Verifica se a última jogada esta completa */
    int inc;
} ESTADO;

/**
\brief Inicializa o valor do estado
@returns Novo estado
*/
ESTADO *inicializar_estado();
/**
\brief Obtém o jogador atual
@param e Apontador para o estado
@returns Jogador atual
*/
int obter_jogador_atual(ESTADO *e);

/**
\brief Obtém o número de jogadas
@param e Apontador para o estado
@returns Número de jogadas
*/
int obter_numero_de_movimentos(ESTADO *e);

/**
\brief Verifica se uam certa casa está livre
@param e Apontador para o estado
@param c Coordenada
@returns 0 - Casa não pode ser jogada \n 1 - Casa pode ser jogada
*/
int casa_esta_livre(ESTADO *e, COORDENADA c);

/**
\brief Devolve o valor de uma casa
@param e Apontador para o estado
@param Linha Linha da jogada
@param Coluna Coluna da jogada
@returns Valor da casa
*/
CASA obter_casa(ESTADO *e, int linha, int coluna);

/**
\brief Muda o valor de uma casa
@param e Apontador para o estado
@param c Coordenada
*/
void mudar_casa(ESTADO *e, COORDENADA c);

/**
\brief Aumenta o valor do comando
@param e Apontador para o estado
*/
void add_comando(ESTADO *e);

/**
\brief Devolve o número de comandos
@param e Apontador para o estado
@returns Número de comandos
*/
int conta_comandos(ESTADO *e);

/**
\brief Muda o jogador
@param e Apontador para o estado
*/
void muda_jogador(ESTADO *e);

/**
\brief Devolve a última jogada
@param e Apontador para o estado do jogo
@returns Coordenada da última jogada
*/
COORDENADA obter_ultima_jogada(ESTADO *e);

/**
\brief Devolve a linha da coordenada dada
@param c Coordenada
@returns Linha de coordenada dada
 */
int obter_linha(COORDENADA c);

/**
\brief Devolve a coluna da coordenada dada
@param c Coordenada
@returns Coluna da coordenada dada
 */
int obter_coluna(COORDENADA c);

/**
\brief Cria uma coordenada com a linha e a coluna dados
@param linha Linha
@param coluna Coluna
@returns Coordenada com a linha e coluna dados
*/
COORDENADA cria_coordenada(int linha, int coluna);

/**
\brief Função que recebe uma linha e guarda no estado de jogo
@param linha Linha
@param numlinha Índice da linha
@param e Apontador para o estado do jogo
*/
void recebelinha(char *linha, int numlinha, ESTADO *e);

/**
\brief Função que adiciona 1 ao número de jogadas
@param e Apontador para o estado do jogo
*/
void add_jogada(ESTADO *e);

/**
\brief Função que retorna coordenadas
@param e Apontador para o estado do jogo
@param i Número da jogada
@param p Jogador atual
@returns 0 - Jogada não existe\n 1 - Jogada existe
*/
int jogada_existe(ESTADO *e, int i, int p);

/**
\brief Função que retorna a jogada a imprimir
@param e Apontador para o estado do jogo
@param i Número da jogada
@param p Jogador atual
@returns String com a jogada
 */
char *obter_jogada(ESTADO *e, int i, int p);

/**
\brief Função que recebe a jogada a ler
@param e Apontador para o estado do jogo
@param c Coluna
@param n Linha
*/
void recebe_jogadas(ESTADO *e, char c, int n);

/**
\brief Função que altera número da jogada atual
@param e Apontador para o estado do jogo
@param num_mov Número do movimento para onde se altera a jogada atual
*/
void pos(ESTADO *e, int num_mov);

/**
\brief Função que dá reset ao tabuleiro
@param e Apontador para o estado do jogo
*/
void reset_tab(ESTADO *e);

/**
\brief Função que verifica o número de jogadas
@param e Apontador para o estado de jogo
*/
void verifica_njogadas(ESTADO *e);

/**
\brief Função que ve as jogadas possiveis
@param e Apontador para o estado de jogo
@param l Uma lista
@returns Lista com as potenciais jogadas
*/
LISTA potenciais_jogadas(ESTADO *e, LISTA l);

/**
\brief Função que calcula a distancia
@param a Coordenada
@param b Coordenada
@returns Distância entre duas casas do tabuleiro
*/
float distancia(COORDENADA a, COORDENADA b);

/**
\brief Função que retira a última jogada
@param e Apontador para o estadp do jogo
*/
void retirar_ultima_jogada(ESTADO *e);

/**
\brief Função que altera o valor do inc
@param e Apontador para o estadp do jogo
@param c Inteiro que pode ser um ou dois consoante o jogador atual
*/
void muda_inc(ESTADO *e, int c);

#endif //PROJETO_LA_DADOS_H
