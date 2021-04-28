#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define MAXBUFFER 1000

int main() {
    int fd[2];
    int i = 0;

    setbuf(stdout, NULL);

    if (pipe(fd) == -1) return -1;

    if (fork() == 0) {
        close(fd[1]);

        dup2(fd[0], 0);
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        
        perror("Exec error");
        return -1;
    } else {
        close(fd[0]);

        if (fork() == 0) {
            dup2(fd[1], 1);
            execlp("ls", "ls", "/etc", NULL);
            perror("Exec error");
            return -1;
        } else {
            wait(&i);
        }

        close(fd[1]);
        wait(&i);
    }

    return WEXITSTATUS(i);
}