#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int numeroFilhos = 0;
int *pids = NULL;

void child_handler(int signum) {
    if (pids == NULL) _exit(-1);

    for (int i = 0; i < numeroFilhos; i++) {
        kill(pids[i], SIGKILL);
    }
    _exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 3) return -1;

    setbuf(stdout, NULL);

    int processos = argc-2;
    pids = malloc(sizeof(int) * processos);

    signal(SIGCHLD, child_handler);
    
    int i, f;
    for (i = 0; i < processos; i++) {
        if ((f = fork()) == 0) {
            execlp("grep", "grep", argv[1], argv[2+i], NULL);
            perror("erro");
            _exit(-1);
        } else if (f == -1) {
            perror("fork gone wrong");
        } else {
            pids[numeroFilhos++] = f;
        }
    }

    return 0;
}