#include "dados.h"
#include "logica.h"
#include <stdio.h>
#include <string.h>
#include <bits/types/FILE.h>
#define BUF_SIZE 1024

void mostrar_tabuleiro(ESTADO *e, FILE *jogo) {
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {
            if (i == 0 && k == 7)
                fprintf(jogo, "2");
            else if (i == 7 && k == 0)
                fprintf(jogo, "1");
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

    e->num_jogadas = -1;
    for (int i = 0; i < 8; i++)
    {
        fgets(linha, 25, jogo);
        recebelinha(linha, i, e);
    }

    fclose(jogo);
}

void gravar (char *ficheiro, ESTADO *e)
{
    FILE *jogo;
    jogo = fopen(ficheiro, "w");
    mostrar_tabuleiro(e, jogo);
    fclose(jogo);
}

void mostrar_prompt(ESTADO *e){
    printf("# %02d",conta_comandos(e));
    printf(" PL%d",obter_jogador_atual(e));
    printf(" (%d)> ",obter_numero_de_jogadas(e));
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    char comando[3];
    char ficheiro[BUF_SIZE];

    mostrar_prompt(e);
    if(fgets(linha, BUF_SIZE, stdin) == NULL)
        return 0;

    if(strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
        COORDENADA coord = {*col - 'a', *lin - '1'};
        jogar(e, coord);
        add_comando(e);
        mostrar_tabuleiro(e, stdout);
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
            mostrar_tabuleiro(e,stdout);
        }
        else if (!strcmp(comando, "gr"))
        {
            gravar(ficheiro, e);
            add_comando(e);
            mostrar_tabuleiro(e,stdout);
        }

    }
    return 1;
}