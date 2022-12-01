#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int status;

    for (int i = 0; i < 10; i++) {
        if (pid = fork() == 0) {
            printf("[filho %d] Iniciando processo %d", i+1, getpid());
            _exit(i+1);
        }
    }

    for (int i = 0; i < 10; i++) {
        pid = wait(&status);
        printf("[pai] Terminado filho de pid %d, com status %d\n", pid, WEXITSTATUS(status));
    }
    printf("[pai] Pid do processo: %d\n", getpid());

    return 0;
}