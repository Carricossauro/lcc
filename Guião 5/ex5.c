#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define MAXBUFFER 10

int system(char *command) {
    if (command == NULL) return 1;
    char *args[MAXBUFFER];
    char *token;
    int c = 0;
    
    token = strtok(command, " ");

    while (token != NULL) {
        args[c++] = token;
        token = strtok(NULL, " ");
    }
    args[c] = NULL;

    int r = 0;
    while (args[r] == " ") {
        r++;
    }

    int ret = execvp(args[r], args+r);

    return ret;
}

int main(int argc, char **argv) {
    if (argc < 2) return -1;

    char *args[MAXBUFFER];
    int pipes[2][MAXBUFFER];
    int k, f;

    setbuf(stdout, NULL);

    int commands = 0;
    // Guardar comandos num array, contar quantos são e abrir os pipes respetivos
    char *token = strtok(argv[1], "|");
    while( token != NULL ) {
        args[commands] = token;
        token = strtok(NULL, "|");
        if (token != NULL && pipe(pipes[commands]) == -1) return -1; // erro se não conseguir criar um pipe
        commands++;
    }
    while (!strcmp(args[commands-1]," ")) commands--;
    args[commands] = NULL;
    printf("Reconhecidos %d comandos\n", commands);

    if (commands == 1) system(argv[0]);

    // Tratar dos redirecionamentos dos pipes
    for (k = 0; k < commands; k++) {
        // printf("\'%s\'\n", args[k]);
        if ((f = fork())== 0) {
            if (k > 0) dup2(pipes[k-1][0],0);
            if (k != commands-1) {
                dup2(pipes[k][1],1);
            }
            break;
        }
    }
    for (int p = 0; p < commands; p++) {
        close(pipes[p][1]);
        close(pipes[p][0]);
    }

    // Executar os vários comandos
    if (f == 0) { // Cada processo filho tem um k único (posiçao no array de argumentos)
        system(args[k]);
        _exit(0);
    } else {
        for (int p = 0; p < commands; p++) {
            int pid = wait(&k);
        }
    }

    return WEXITSTATUS(k);
}

/*
ngl este foi fodido
*/