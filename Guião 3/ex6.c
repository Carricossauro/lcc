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
    
    token = strtok(command, " ");

    while (token != NULL) {
        args[c++] = token;
        token = strtok(NULL, " ");
    }
    args[c] = NULL;

    if (fork() == 0) {
        int ret = execvp(args[0], args);
        
        _exit(ret);
    }

    int status;
    pid_t pid = wait(&status);
    return status;
}

int main(int argc, char **argv) {
    return system("ls");
}