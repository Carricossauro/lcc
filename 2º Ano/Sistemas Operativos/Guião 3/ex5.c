#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char **argv) {
    pid_t pid;
    int status;
    for (int i = 1; i < argc; i++) {
        if (fork() == 0) {

            char *args[] = {argv[i], NULL};
            printf("[Processo %d] ", getpid());

            execvp(argv[i], args);
            // execv(argv[i], args); -> Para correr ficheiros que não estão em $PATH

            _exit(0);
        }
    }

    for (int i = 1; i < argc; i++) {
        pid = wait(&status);
    }

    return 0;
}