#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define MAXBUFFER 1000

int main() {
    int fd[2];
    int i = 0;
    char buffer[MAXBUFFER];
    char line[] = "ola maluco";

    setbuf(stdout, NULL);

    if (pipe(fd) == -1) return -1;

    if (fork() == 0) {
        close(fd[1]);

        dup2(fd[0], 0);
        close(fd[0]);

        execlp("wc", "wc", NULL);
        
        perror("Fork");
        return -1;        
    } else {
        close(fd[0]);
        
        while(read(0, buffer, 1)) {
            write(fd[1], buffer, 1);
        }

        close(fd[1]);
        wait(&i);
    }

    return WEXITSTATUS(i);
}