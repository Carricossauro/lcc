#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define numberInInterval(min, max) rand()%(max-min+1)+min

// ./a.out [número de linhas] [número de colunas] [número para procurar]
int main(int argc, char* argv[]) {
    pid_t pid;
    int status;
    if (argc < 4) return 1;
    
    int x = atoi(argv[3]);
    int LINHAS = atoi(argv[1]);
    int COLUNAS = atoi(argv[2]);

    // Originar matriz aleatória
    int matriz[LINHAS][COLUNAS];
    srand(time(NULL));
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            matriz[i][j] = numberInInterval(0,50);

    // Loop principal - Padrão de filhos sequenciais
    for (int i = 0; i < LINHAS; i++) {
        if (pid = fork() == 0) {
            for (int k = 0; k < COLUNAS; k++)
                if (matriz[i][k] == x) _exit(1);
            _exit(0);
        } else {
            pid = wait(&status);
            printf("Linha %d, status: %d\n", i+1, WEXITSTATUS(status));
        }
    }

    // Mostrar resultados
    printf("Matriz era:\n");
    for (int i = 0; i < LINHAS; i++) {
        for (int k = 0; k < COLUNAS; k++)
            printf(" %d", matriz[i][k]);
        putchar('\n');
    }

    return 0;
}