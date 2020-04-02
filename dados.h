/**
@file dados.h
Definição do estado e das funções que o manipulam
*/

#ifndef PROJETO_LA_DADOS_H
#define PROJETO_LA_DADOS_H

typedef enum {VAZIO, BRANCA, PRETA} CASA;

/**
\brief Tipo de dados para as coordenadas
*/
typedef struct {
    int coluna;
    int linha;
} COORDENADA;

/**
\brief Tipo de dados para a jogada
*/
typedef struct {
    COORDENADA jogador1;
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
    /** Ultima Jogada */
    COORDENADA ultima_jogada;
    /** Jogadas */
    JOGADAS jogadas;
    /** Numero de jogadas */
    int num_jogadas;
    /** Jogador Atual */
    int jogador_atual;
    /** Numero de comandos */
    int num_comandos;
    /** Numero de movimento*/
    int num_movimento;
} ESTADO;

/**
\brief Inicializa o valor do estado
@returns Novo estado
*/
ESTADO *inicializar_estado();
/**
\brief Obtem o jogador atual
@param e Apontador para o estado
@returns Jogador atual
*/
int obter_jogador_atual(ESTADO *e);

/**
\brief Obtem o número de jogadas
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
@param linha Linha da jogada
@param coluna Coluna da jogada
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
@param numlinha Index da linha
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
@param e Apontado rpara o estado do jogo
@param i Número da jogada
@param p Jogador atual
@returns String com a jogada
 */
char *obter_jogada(ESTADO *e, int i, int p);

/**
\brief Função que recebe a jogada a ler
@param e Apontador para o estado do jogo
@param c coluna
@param n linha
*/
void recebe_jogadas(ESTADO *e, char c, int n);

/**
\brief Função que altera número da jogada atual
@param e Apontador para o estado do jogo
@param num_mov numero do movimento para onde se altera a jogada atual
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
#endif //PROJETO_LA_DADOS_H
