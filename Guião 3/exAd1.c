#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

#define MAXBUFFER 1000

int mySystem(char **argv) {
    if (argv[0] == NULL) return 1;
    
    if (fork() == 0) {
        execvp(argv[0], argv);
        
        _exit(127);
    }

    int status;
    pid_t pid = wait(&status);
    return status;
}

int split(char *buffer, char **args) { 
    // Guarda os comandos de um buffer para um array de strings
    char command[MAXBUFFER];
    int k,i = 0; // Posição a ler no buffer
    int c = 0; // Número de comandos guardados
    while (buffer[i] != '\0') {
        if (buffer[i] == ' ') i++;

        for (k = 0; i < MAXBUFFER && buffer[i] != '\0' && buffer[i] != ' '; k++, i++) {
            command[k] = buffer[i];
        }
        // i == MAXBUFFER ou
        // buffer[i] == '\0' ou
        // buffer[i] == ' '
        if (i == MAXBUFFER) return 1;

        command[k] = '\0';

        args[c] = malloc(sizeof(char) * k);
        strcpy(args[c++], command);
    }
    args[c] = NULL;

    return 0;
}

ssize_t readln(char *line) {
	ssize_t res = 0;
	ssize_t i = 0;
    
	while ((res = read(0, &line[i], 1)) > 0 && ((char) line[i] != '\n')) {
		i+=res;
	}

	return i;
}

int main() {
    int exit = 0;
    char buffer[MAXBUFFER];
    char *args[MAXBUFFER];
    char ch;
    int r;

    while (!exit) {
        r = readln(buffer);
        buffer[r] = '\0';

        if (split(buffer, args)) continue;

        if (!strcmp(args[0], "exit")) return 0;
        
        mySystem(args);
    }

    return 1;
}