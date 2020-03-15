#ifndef PROJETO_LA_DADOS_H
#define PROJETO_LA_DADOS_H

typedef enum {VAZIO, BRANCA, PRETA} CASA;

typedef struct {
    int coluna;
    int linha;
} COORDENADA;

typedef struct {
    COORDENADA jogador1;
    COORDENADA jogador2;
} JOGADA;

typedef JOGADA JOGADAS[32];

typedef struct {
    CASA tab[8][8];
    COORDENADA ultima_jogada;
    JOGADAS jogadas;
    int num_jogadas;
    int jogador_atual;
} ESTADO;

ESTADO *inicializar_estado();
int obter_jogador_atual(ESTADO *e);
int obter_numero_de_jogadas(ESTADO *e);
int obter_estado_casa(ESTADO *e, COORDENADA c);
CASA obter_casa(ESTADO *e, int linha, int coluna);

#endif //PROJETO_LA_DADOS_H
