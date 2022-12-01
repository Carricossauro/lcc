#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define MAXBUFFER 10

int main() {
    int fd[2];
    int i = 0;
    char buffer[MAXBUFFER];
    char line[] = "ola maluco";

    setbuf(stdout, NULL);

    if (pipe(fd) == -1) return -1;

    if (fork() == 0) {
        close(fd[1]);

        while(read(fd[0], buffer+i, 1)) {
            i++;
            printf("Read nº %d\n", i);
        }
        buffer[i] = '\0';

        printf("Lido \"%s\"\n", buffer);
        close(fd[0]);
    } else {
        close(fd[0]);
        
        for (int i = 0; i < strlen(line); i++) {
            sleep(1);
            write(fd[1], line+i, 1);
        }

        close(fd[1]);
        wait(&i);

        return WEXITSTATUS(i);
    }
    return 0;
}