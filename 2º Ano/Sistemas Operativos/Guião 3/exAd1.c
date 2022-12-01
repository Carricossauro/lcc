#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>

#define MAXBUFFER 100

int system(char *command) {
    if (command == NULL) return 1;
    char *args[MAXBUFFER];
    char *token;
    int c = 0;
    int background = 0;
    
    token = strtok(command, " ");

    while (token != NULL) {
        args[c++] = token;
        token = strtok(NULL, " ");
    }
    if (!strcmp(args[c-1], "&")) {
        background = 1;
        c--;
    }
    args[c] = NULL;

    if (fork() == 0) {
        int ret = execvp(args[0], args);
        
        _exit(ret);
    }

    int status = 0;
    pid_t pid;
    if (!background) pid = wait(&status);
    return status;
}

ssize_t readln(char *line) {
	ssize_t res = 0;
	ssize_t i = 0;
    
	while ((res = read(0, &line[i], 1)) > 0 && ((char) line[i] != '\n')) {
		i+=res;
	}
    	line[i] = '\0';
	return i;
}

int main(int argc, char **argv) {
    char buffer[MAXBUFFER];

    while (1) {
        readln(buffer);

        if (!strcmp(buffer, "exit")) break;

        system(buffer);
    }

    return 0;
}