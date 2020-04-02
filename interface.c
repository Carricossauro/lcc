#include "dados.h"
#include "logica.h"
#include "interface.h"
#include <stdio.h>
#include <string.h>
#include <bits/types/FILE.h>
#include <stdlib.h>
#define BUF_SIZE 1024

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
        fgets(linha, 25, jogo);
        recebelinha(linha, i, e);
    }

    fgets(linha, 25, jogo);
    while (fgets(linha, 25, jogo) != NULL)
    {
        if (sscanf(linha, "%s %c%d %c%d", str, &c1, &n1, &c2, &n2) == 5) {
            recebe_jogadas(e, c1, n1);
            recebe_jogadas(e, c2, n2);
        } else if (sscanf(linha, "%s %c%d", str, &c1, &n1) == 3) {
            recebe_jogadas(e, c1, n1);
        }
    }

    fclose(jogo);
}

void gravar (char *ficheiro, ESTADO *e)
{
    FILE *jogo;
    jogo = fopen(ficheiro, "w");
    mostrar_tabuleiro(e, jogo);
    fprintf(jogo, "\n");
    movs(jogo, e);
    fclose(jogo);
}

void mostrar_prompt(ESTADO *e){
    printf("# %02d",conta_comandos(e));
    printf(" PL%d",obter_jogador_atual(e));
    printf(" (%d)> ",obter_numero_de_jogadas(e));
}

void movs(FILE *jogo, ESTADO *e){
    char *str;
    for (int i = 0; i <= obter_numero_de_jogadas(e); i++) {
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

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    char comando[5];
    char ficheiro[BUF_SIZE];

    mostrar_tabuleiro(e, stdout);
    mostrar_prompt(e);
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;

    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        jogar(e, coord);
        add_comando(e);
    }
    else if(!strcmp(linha, "Q\n"))
    {
        return 0;
    }
    else if(sscanf(linha, "%s %s", comando, ficheiro) == 2)
    {
        if(!strcmp(comando, "ler"))
        {
            ler(ficheiro, e);
            add_comando(e);
        }
        else if (!strcmp(comando, "gr"))
        {
            gravar(ficheiro, e);
            add_comando(e);
        }
    }
    else if(sscanf(linha, "%s", comando) == 1 && !strcmp(comando, "movs"))
    {
        movs(stdout, e);
        add_comando(e);
        putchar('\n');
    }
    return 1;
}