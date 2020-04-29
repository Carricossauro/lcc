#ifndef BOT_BOT_H
#define BOT_BOT_H

#include <bits/types/FILE.h>

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
/brief Função que lê um ficheiro
@param ficheiro Ficheiro
@param e Apontador para o Estado do jogo
*/
void ler (char *ficheiro, ESTADO *e);

/**
/brief Função que grava um ficheiro
@param ficheiro Ficheiro
@param e Apontador para o Estado do jogo
*/
void gravar (char *ficheiro, ESTADO *e);

/**
/brief Função que mostra os movimentos
@param jogo File stream para o output
@param e Apontador para o Estado do jogo
*/
void movs (FILE *jogo, ESTADO *e);

void mostrar_tabuleiro(ESTADO *e, FILE *jogo);

/**
\brief Função que recebe uma linha e guarda no estado de jogo
@param linha Linha
@param numlinha Índice da linha
@param e Apontador para o estado do jogo
*/
void recebelinha(char *linha, int numlinha, ESTADO *e);

/**
\brief Função que recebe a jogada a ler
@param e Apontador para o estado do jogo
@param c Coluna
@param n Linha
*/
void recebe_jogadas(ESTADO *e, char c, int n);

/**
\brief Função que altera o valor do inc
@param e Apontador para o estadp do jogo
@param c Inteiro que pode ser um ou dois consoante o jogador atual
*/
void muda_inc(ESTADO *e, int c);

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
\brief Função que altera número da jogada atual
@param e Apontador para o estado do jogo
@param num_mov Número do movimento para onde se altera a jogada atual
*/
void pos(ESTADO *e, int num_mov);

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
\brief Função que dá reset ao tabuleiro
@param e Apontador para o estado do jogo
*/
void reset_tab(ESTADO *e);

/**
\brief Função que recebe uma coordenada e joga quando é válida
@param e Apontador para o estado do jogo
@param c Coordenada da jogada
@returns 1 - Jogada Válida \n 0 - Jogada Inválida
*/
int jogar(ESTADO *e, COORDENADA c);

/**
\brief Muda o valor de uma casa
@param e Apontador para o estado
@param c Coordenada
*/
void mudar_casa(ESTADO *e, COORDENADA c);

/**
\brief Verifica se uam certa casa está livre
@param e Apontador para o estado
@param c Coordenada
@returns 0 - Casa não pode ser jogada \n 1 - Casa pode ser jogada
*/
int casa_esta_livre(ESTADO *e, COORDENADA c);

/**
\brief Muda o jogador
@param e Apontador para o estado
*/
void muda_jogador(ESTADO *e);

/**
\brief Função que adiciona 1 ao número de jogadas
@param e Apontador para o estado do jogo
*/
void add_jogada(ESTADO *e);

/**
/brief Função que joga pelo jogador
@param e Apontador para o Estado do jogo
*/
void jog2(ESTADO *e);

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
@param jogador Jogador 1 ou 2
@returns valor que uma jogada tem
*/
float valor_jogada(COORDENADA c, ESTADO *e, int jogador);

/**
\brief Função que determina se o jogo foi ganho
@param e Apontado para o estado do jogo
@param c Coordenada da última jogada
@returns 0 - Jogo não acabou \n 1 - Vitória do jogador 1 \n 2 - Vitória do jogador 2
*/
int gameOver(ESTADO *e, COORDENADA c);

/**
/brief Função que joga pelo jogador
@param e Apontador para o Estado do jogo
*/
void jog (ESTADO *e);

/**
\brief Função que retira a última jogada
@param e Apontador para o estadp do jogo
*/
void retirar_ultima_jogada(ESTADO *e);

/**
\brief Cria uma coordenada com a linha e a coluna dados
@param linha Linha
@param coluna Coluna
@returns Coordenada com a linha e coluna dados
*/
COORDENADA cria_coordenada(int linha, int coluna);

/**
\brief Definição da lista ligada genérica
*/
typedef struct nodo {
    /** Apontador para um valor genérico*/
    void *valor;
    /** Apontador para o próximo elemento da lista*/
    struct nodo *proximo;
} NODO, *LISTA;

/**
\brief Função que cria um lista ligada
@returns Apontador para a lista ligada
*/
LISTA criar_lista();

/**
\brief Função que insere um valor à cabeça
@param l Lista ligada
@param valor Valor a ser adicionado
@returns Apontador para a lista ligada
 */
LISTA insere_cabeca(LISTA l, void *valor);

/**
\brief Função que devolve a cabeça da lista
@param l Lista ligada
@returns Valor guardado na cabeça
*/
void *devolve_cabeca(LISTA l);

/**
\brief Função que devolve o próximo valor da lista
@param l Lista ligada
@returns Lista que começa no elemento seguinte da lista dada
 */
LISTA proximo(LISTA l);

/**
\brief Função que remove a cabeça da lista
@param L Lista ligada
@returns Cauda da lista ligada
 */
LISTA remove_cabeca(LISTA L);

/**
\brief Função que verifica se a lista está vazia
@param L Lista ligada
@returns 1 - Lista está vazia |n 0 - Lista não está vazia
 */
int lista_esta_vazia(LISTA L);

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
\brief Devolve o valor de uma casa
@param e Apontador para o estado
@param Linha Linha da jogada
@param Coluna Coluna da jogada
@returns Valor da casa
*/
CASA obter_casa(ESTADO *e, int linha, int coluna);


#endif //BOT_BOT_H
