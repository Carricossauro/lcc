/**
@file bot.c
Definição do estado e das funções que o manipulam
*/

#include "bot.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>


ESTADO *inicializar_estado() {
    ESTADO *e = (ESTADO *) malloc(sizeof(ESTADO));
    e->inc = 0;
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

void ler (char *ficheiro, ESTADO *e)
{
    FILE *jogo;
    jogo = fopen(ficheiro, "r");
    char linha[25];
    char c1, c2;
    int n1, n2;
    char str[25];

    free(e);
    e = inicializar_estado();

    for (int i = 7; i >= 0; i--)
    {
        if(fgets(linha, 25, jogo)) {
            recebelinha(linha, i, e);
        }
    }

    if(fgets(linha, 25, jogo)) {
        while (fgets(linha, 25, jogo) != NULL) {
            if (sscanf(linha, "%s %c%d %c%d", str, &c1, &n1, &c2, &n2) == 5) {
                recebe_jogadas(e, c1, n1);
                recebe_jogadas(e, c2, n2);
            } else if (sscanf(linha, "%s %c%d", str, &c1, &n1) == 3) {
                recebe_jogadas(e, c1, n1);
            }
        }
    }

    fclose(jogo);
}

void gravar (char *ficheiro, ESTADO *e)
{
    muda_inc(e, obter_jogador_atual(e));
    pos(e, obter_numero_de_movimentos(e));
    FILE *jogo;
    jogo = fopen(ficheiro, "w");
    mostrar_tabuleiro(e, jogo);
    fprintf(jogo, "\n");
    movs(jogo, e);
    fclose(jogo);
    muda_inc(e, 0);
}

void movs(FILE *jogo, ESTADO *e){
    pos(e, obter_numero_de_movimentos(e));
    char *str;
    for (int i = 0; i < obter_numero_de_movimentos(e); i++) {
        if (jogada_existe(e, i, 1)) {
            fprintf(jogo, "%02d: %s", i+1, (str = obter_jogada(e, i, 1)));
            free(str);
        } else break;

        if (jogada_existe(e, i, 2)) {
            fprintf(jogo, " %s\n", (str = obter_jogada(e, i, 2)));
            free(str);
        } else break;
    }
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

void muda_inc(ESTADO *e, int c) {
    if (e->inc == 0)
        e->inc = c;
    else if (c == 0)
        e->inc = 0;
}

int obter_jogador_atual(ESTADO *e) {

    return e->jogador_atual;
}

int obter_numero_de_movimentos(ESTADO *e) {

    return e->num_movimento;
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

int jogar(ESTADO *e, COORDENADA c)
{
    if(casa_esta_livre(e, c))
    {
        mudar_casa(e, c);
        muda_jogador(e);
        add_jogada(e);
        return 1;
    }
    else
        return 0;
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

void muda_jogador(ESTADO *e){
    if(e->jogador_atual == 1) {
        e->jogador_atual = 2;
    }
    else {
        e->jogador_atual = 1;
    }
}

void add_jogada(ESTADO *e) {
    if (e->jogador_atual == 1) {
        if (e->num_jogadas++ < e->num_movimento++)
            e->num_movimento--;
    }
}

void jog2(ESTADO *e){
    COORDENADA c = obter_ultima_jogada(e), *a, *p = NULL;
    float x = INT_MIN;
    float y;

    if (obter_jogador_atual(e) == 1) {
        for (int i = obter_linha(c) - 1; i <= obter_linha(c) + 1 ; i++) {
            for (int j = obter_coluna(c) - 1; j <= obter_coluna(c) + 1 ; j++) {
                a = malloc(sizeof(COORDENADA));
                a->linha = i;
                a->coluna = j;
                if((y = Minimax(7, *a, e, 1)) > x && casa_esta_livre(e, *a)){
                    p = a;
                    x = y;
                }else free(a);
            }
        }
    } else {
        for (int i = obter_linha(c) + 1; i >= obter_linha(c) - 1; i--) {
            for (int j = obter_coluna(c) + 1; j >= obter_coluna(c) - 1 ; j--) {
                a = malloc(sizeof(COORDENADA));
                a->linha = i;
                a->coluna = j;
                if((y = Minimax(7, *a, e, 1)) > x && casa_esta_livre(e, *a)){
                    p = a;
                    x = y;
                }else free(a);
            }
        }
    }
    if (x != 1) {
        if(p != NULL){
            jogar(e, *p);
            free(p);
        }
    } else {
        jog(e);
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

arvore inicializa_arvore(ESTADO *e, COORDENADA c, int jog)
{
    arvore tree = malloc(sizeof(struct Tree));
    tree->nodo = c;
    COORDENADA *c1;
    int a = 0;
    if (jog == 1) {
        for (int i = c.linha - 1; i <= c.linha + 1 ; i++)
        {
            for (int j = c.coluna - 1; j <= c.coluna + 1; j++)
            {
                c1 = malloc(sizeof(COORDENADA));
                c1->linha = i;
                c1->coluna = j;

                if(c1->linha != c.linha || c1->coluna != c.coluna)
                {
                    if(casa_esta_livre(e, *c1))
                    {
                        tree->proximo[a] = c1;
                        a++;
                    }
                    else
                    {
                        tree->proximo[a] = NULL;
                        a++;
                        free(c1);
                    }
                }
                else
                {
                    free(c1);
                }
            }
        }
    }
    else {
        for (int i = c.linha + 1; i >= c.linha - 1 ; i--)
        {
            for (int j = c.coluna + 1; j >= c.coluna - 1; j--)
            {
                c1 = malloc(sizeof(COORDENADA));
                c1->linha = i;
                c1->coluna = j;

                if(c1->linha != c.linha || c1->coluna != c.coluna)
                {
                    if(casa_esta_livre(e, *c1))
                    {
                        tree->proximo[a] = c1;
                        a++;
                    }
                    else
                    {
                        tree->proximo[a] = NULL;
                        a++;
                        free(c1);
                    }
                }
                else
                {
                    free(c1);
                }
            }
        }
    }
    return tree;
}

float Minimax(int altura, COORDENADA c, ESTADO *e, int jog)
{
    float k = INT_MIN;
    float valor;
    if (jogar(e, c)) {
        arvore tree = inicializa_arvore(e, c, jog);

        if(altura == 0 || gameOver(e, c))
            k = valor_jogada(c, e, jog);
        else {

            for (int i = 0; i < 8; i++)
            {
                if(tree->proximo[i] != NULL)
                {
                    valor = Minimax(altura - 1, *tree->proximo[i], e, (jog == 1) ? 2 : 1);
                    if(valor > k)
                    {
                        k = valor;
                    }
                }
            }
        }
        retirar_ultima_jogada(e);
    }
    return k;
}

float valor_jogada(COORDENADA c, ESTADO *e, int jogador){
    float a = 1;
    int x = gameOver(e,c);
    if (x != 0) {
        if(x == jogador)
            a = 100;
        else if (x != jogador)
            a = -100;
    }
    return a;
}

int gameOver(ESTADO *e, COORDENADA c) {
    COORDENADA co;
    if (c.linha == 7 && c.coluna == 7) return 2;
    if (c.linha == 0 && c.coluna == 0) return 1;

    int lin = obter_linha(c), col = obter_coluna(c);
    for (int i = lin - 1; i <= lin + 1; i++) {
        for (int k = col - 1; k <= col + 1; k++) {
            co = cria_coordenada(i,k);
            if (casa_esta_livre(e, co)) return 0;
        }
    }
    return (obter_jogador_atual(e) == 1 ? 2 : 1);
}

void jog(ESTADO *e){
    float d = INT_MAX;

    COORDENADA c, origem, *a;

    LISTA l = criar_lista();
    l = potenciais_jogadas(e, l);

    LISTA t = l;

    if (obter_jogador_atual(e) == 1){
        origem.linha = 0;
        origem.coluna = 0;
    }
    else {
        origem.linha = 7;
        origem.coluna = 7;
    }

    while (!lista_esta_vazia(t)){
        a = (COORDENADA*) devolve_cabeca(t);
        distancia(*a, origem);
        if (distancia(*a, origem) < d){
            d = distancia(*a, origem);
            c = *a;
        }
        t = proximo(t);
    }

    jogar(e, c);

    while (!lista_esta_vazia(l)) {
        l = remove_cabeca(l);
    }
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

COORDENADA cria_coordenada(int linha, int coluna) {
    COORDENADA c;
    c.linha = linha;
    c.coluna = coluna;
    return c;
}

LISTA criar_lista() {
    LISTA l = malloc(sizeof(NODO));
    l->valor = NULL;
    l->proximo = NULL;
    return l;
}

LISTA insere_cabeca(LISTA l, void *valor) {
    if (l->valor == NULL) {
        l->valor = valor;
        return l;
    } else {
        LISTA t = malloc(sizeof(NODO));
        t->valor = valor;
        t->proximo = l;
        return t;
    }
}

void *devolve_cabeca(LISTA l) {
    return l->valor;
}

LISTA proximo(LISTA l) {
    return l->proximo;
}

LISTA remove_cabeca(LISTA l) {
    LISTA t = l->proximo;
    free(l);
    return t;
}

int lista_esta_vazia(LISTA l) {
    if (l == NULL || (l->valor == NULL &&  l->proximo == NULL))
        return 1;
    return 0;
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

void mostrar_tabuleiro(ESTADO *e, FILE *jogo) {
    for (int i = 7; i >= 0; i--) {
        for (int k = 0; k < 8; k++) {
            if (i == 0 && k == 0)
                fprintf(jogo, "1");
            else if (i == 7 && k == 7)
                fprintf(jogo, "2");
            else
                fprintf(jogo, ((obter_casa(e, k, i) == PRETA) ? "#" : ((obter_casa(e, k, i) == BRANCA) ? "*" : ".")));
        }
        fprintf(jogo, "\n");
    }
}

CASA obter_casa(ESTADO *e, int coluna, int linha) {
    return e->tab[linha][coluna];
}

/**
\brief Definição que inicializa o bot
@param argc Número de argumentos recebidos pelo bot
@param argv Array com os strings dos argumentos recebidos
*/
int main(int argc, char **argv) {

    if(argc == 3){

        ESTADO *e = inicializar_estado();
        ler(argv[1], e);
        jog2(e);
        muda_inc(e, obter_jogador_atual(e));
        gravar(argv[2], e);
    }
}
