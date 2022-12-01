#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int status = 0;

    for (int i = 1; i < 11; i++) {
        if (pid = fork() == 0) {
            printf("Filho:\n");
            printf("Pid do próprio: %d\n", getpid());
            printf("Pid do pai: %d\n", getppid());
            _exit(i);
        } else {
            pid = wait(&status);
            printf("Pai: Acabou filho %d, pid %d\n", i, pid);
        }
    }


    return 0;
}