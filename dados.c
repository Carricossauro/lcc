#include "interface.h"
#include "dados.h"
#include "logica.h"
#include "listas.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e->num_comandos = 0;
    e->jogador_atual = 1;
    for (int linha = 0; linha < 8; linha++){
        for (int coluna = 0; coluna < 8; coluna++){
            e->tab[coluna][linha] = VAZIO;
        }
    }
    e->tab[4][4] = BRANCA;
    e->ultima_jogada.coluna = 4;
    e->ultima_jogada.linha = 4;
    e->num_movimento = 1;
    e->num_jogadas = 1;
    return e;
}
void muda_jogador(ESTADO *e){
    if(e->jogador_atual == 1) {
        e->jogador_atual = 2;
    }
    else {
        e->jogador_atual = 1;
    }
}

void add_comando(ESTADO *e){
    e->num_comandos += 1;
}

int conta_comandos(ESTADO *e){
    return e->num_comandos;
}

int obter_jogador_atual(ESTADO *e) {

    return e->jogador_atual;
}

int obter_numero_de_movimentos(ESTADO *e) {

    return e->num_movimento;
}

int casa_esta_livre(ESTADO *e, COORDENADA c) {
    int coluna = c.coluna;
    int linha = c.linha;
    int lin = e->ultima_jogada.linha;
    int col = e->ultima_jogada.coluna;
    int r = 0;

    if (linha < 0 || linha > 7 || coluna < 0 || coluna > 7)
        r = 0;
    else if (e->tab[linha][coluna] == VAZIO && linha >= lin - 1 && linha <= lin + 1 && coluna >= col - 1 && coluna <= col + 1)
        r = 1;
    return r;
}

CASA obter_casa(ESTADO *e, int coluna, int linha) {
    return e->tab[linha][coluna];
}

void mudar_casa(ESTADO *e, COORDENADA c)
{
    int linha = e -> ultima_jogada.linha;
    int coluna = e -> ultima_jogada.coluna;

    e -> tab[linha][coluna] = PRETA;
    e -> tab[c.linha][c.coluna] = BRANCA;

    e->ultima_jogada.linha = c.linha;
    e->ultima_jogada.coluna = c.coluna;

    if(e->jogador_atual == 1){
        e->jogadas[e->num_jogadas-1].jogador1.coluna = c.coluna;
        e->jogadas[e->num_jogadas-1].jogador1.linha = c.linha;
    } else {
        e->jogadas[e->num_jogadas-1].jogador2.coluna = c.coluna;
        e->jogadas[e->num_jogadas-1].jogador2.linha = c.linha;
    }

}

COORDENADA obter_ultima_jogada(ESTADO *e) {
    return e->ultima_jogada;
}

int obter_linha(COORDENADA c) {
    return c.linha;
}

int obter_coluna(COORDENADA c) {
    return c.coluna;
}

COORDENADA cria_coordenada(int linha, int coluna) {
    COORDENADA c;
    c.linha = linha;
    c.coluna = coluna;
    return c;
}

void recebelinha(char *linha, int numlinha, ESTADO *e)
{
    for (int i = 0; i < 8; i++)
    {
        if (linha[i] == '*') {
            e->tab[numlinha][i] = BRANCA;
            e->ultima_jogada.coluna = i;
            e->ultima_jogada.linha = numlinha;
        } else if (linha[i] == '#') {
            e->tab[numlinha][i] = PRETA;
        } else e -> tab[numlinha][i] = VAZIO;
    }
}

void add_jogada(ESTADO *e) {
    if(e->jogador_atual == 1)
    {
        if(e -> num_jogadas++ < e -> num_movimento++)
            e -> num_movimento--;
    }
}

int jogada_existe(ESTADO *e, int i, int p) {
    if (i < e->num_movimento-1)
        return 1;
    else if (e->num_movimento-1 == i) {
        if (p == 2)
            return 0;
        else if (e->jogador_atual == 2)
            return 1;
    }
    return 0;
}

char *obter_jogada(ESTADO *e, int i, int p) {
    char *str = calloc(3, sizeof(char));
    if (p == 1) {
        str[0] = e->jogadas[i].jogador1.coluna + 'a';
        str[1] = e->jogadas[i].jogador1.linha + '1';
    } else {
        str[0] = e->jogadas[i].jogador2.coluna + 'a';
        str[1] = e->jogadas[i].jogador2.linha + '1';
    }
    return str;
}

void recebe_jogadas(ESTADO *e, char c, int n)
{
    if(e -> jogador_atual == 1)
    {
        e -> jogadas[e -> num_jogadas-1].jogador1.coluna = c - 'a';
        e -> jogadas[e -> num_jogadas-1].jogador1.linha = n - 1;

        e -> jogador_atual = 2;
    }
    else
    {
        e -> jogadas[e -> num_jogadas-1].jogador2.coluna = c - 'a';
        e -> jogadas[e -> num_jogadas-1].jogador2.linha = n - 1;

        e -> jogador_atual = 1;
        e -> num_jogadas++;
        e -> num_movimento++;
    }
}

void reset_tab(ESTADO *e){
    e->jogador_atual = 1;
    for (int linha = 0; linha < 8; linha++){
        for (int coluna = 0; coluna < 8; coluna++){
            e->tab[coluna][linha] = VAZIO;
        }
    }
    e->tab[4][4] = BRANCA;
    e->ultima_jogada.coluna = 4;
    e->ultima_jogada.linha = 4;
    e -> num_jogadas = 1;
}

void pos(ESTADO *e, int num_mov){
    int k = (e ->inc == 2 && num_mov == e -> num_movimento);

    reset_tab(e);
    int i=0;
    if (e->num_movimento != 1) {
        do {
            if (num_mov != 0) {
                jogar(e, e->jogadas[i].jogador1);
                jogar(e, e->jogadas[i].jogador2);
            }
        } while (i++ < num_mov-1 && i != e->num_movimento-1);
    }
    if (k)
    {
        jogar(e, e -> jogadas[num_mov-1].jogador1);
    }
}

void verifica_njogadas(ESTADO *e){
    if(e -> num_movimento != e -> num_jogadas)
    {
        e -> num_movimento = e -> num_jogadas;
    }
}

LISTA potenciais_jogadas(ESTADO *e, LISTA l){

    COORDENADA c1 = obter_ultima_jogada(e);
    COORDENADA c2;
    COORDENADA *c;

    for (int i = c1.linha - 1; i <= c1.linha + 1; i++){
        for (int j = c1.coluna - 1; j <= c1.coluna + 1; ++j) {
            c2.linha = i;
            c2.coluna = j;
            if (casa_esta_livre(e, c2)){
                c = malloc(sizeof(COORDENADA));
                c->linha = c2.linha;
                c->coluna = c2.coluna;
                l = insere_cabeca(l, c);
            }
        }
    }

    return l;
}

float distancia(COORDENADA c1 ,COORDENADA c2){

    float d;
    d = sqrtf(pow(c1.linha - c2.linha, 2) + pow(c1.coluna - c2.coluna, 2));

    return d;
}

void retirar_ultima_jogada(ESTADO *e)
{
    if (e->num_movimento == 2 && e->jogador_atual == 1) {
        e->num_movimento = 1;
        e->jogador_atual = 2;
        e->inc = 2;
    }
    else if (e->jogador_atual == 2) {
        e->jogador_atual = 1;
    } else {
        e->num_movimento--;
        e->jogador_atual = 2;
        e->inc = 2;
    }
    pos(e, e->num_movimento);
    e -> num_jogadas = e -> num_movimento;
    e->inc = 0;
}

void muda_inc(ESTADO *e, int c) {
    if (e->inc == 0)
        e->inc = c;
    else if (c == 0)
        e->inc = 0;
}