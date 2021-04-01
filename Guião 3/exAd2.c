#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

int mySystem(char **argv) {
    if (argv[0] == NULL) return 1;
    
    if (fork() == 0) {
        execvp(argv[0], argv);
        perror("error");
        _exit(127);
    }

    int status;
    pid_t pid = wait(&status);
    return status;
}

// ./controlador ./a ./b ./c
int main(int argc, char **argv) {
    if (argc < 2) return 1;

    for (int i = 1; i < argc; i++) {
        char *args[2] = {argv[i], NULL};
        int rep = 1;

        while (mySystem(args) != 0) rep++;

        printf("%s %d\n", argv[i], rep);
    }

    return 0;
}