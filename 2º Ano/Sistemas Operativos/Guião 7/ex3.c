#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>

// abcdef ex3

int numeroFilhos = 0;
int *pids = NULL;
int filho = -5;

void main_handler(int signum) {
    if (pids == NULL) _exit(-1);

    for (int i = 0; i < numeroFilhos; i++) {
        printf("Tentando fechar %d\n", pids[i]);
        kill(pids[i], SIGUSR1);
    }
    _exit(0);
}

void child_handler(int signum) {
    if (filho != -5 && filho != -1) {
        kill(filho, SIGKILL);
    }
    printf("Fechando filho.\n");
    _exit(0);
}

void monitor(char **argv, int i) {
    signal(SIGUSR1, child_handler);
    signal(SIGALRM, child_handler);
    signal(SIGCHLD, child_handler);
    alarm(10);
    if ((filho = fork()) == 0) {
        execlp("grep", "grep", argv[1], argv[2+i], NULL);
        perror("erro");
        _exit(-1);
    }
    pause();
    _exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 3) return -1;

    setbuf(stdout, NULL);

    int processos = argc-2;
    int ar[processos];
    pids = ar;

    signal(SIGCHLD, main_handler);
    signal(SIGINT, main_handler);
    
    int i, f;
    for (i = 0; i < processos; i++) {
        sleep(1); // Esta aqui para fazer testes
        if ((f = fork()) == 0) {
            monitor(argv, i);
            _exit(-1);
        } else if (f == -1) {
            perror("fork gone wrong");
        } else {
            printf("Processo filho -> %d -> %s\n", f, argv[2+i]);
            pids[numeroFilhos++] = f;
        }
    }

    pause();

    return 0;
}