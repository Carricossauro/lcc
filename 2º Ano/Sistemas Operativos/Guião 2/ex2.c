#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int status;

    if (pid = fork() == 0) {
        printf("Filho:\n");
        printf("Pid do próprio: %d\n", getpid());
        printf("Pid do pai: %d\n", getppid());
    } else {
        pid = wait(&status);
        printf("Pai:\n");
        printf("Pid do filho: %d\n", pid);
        printf("Pid do próprio: %d\n", getpid());
        printf("Pid do pai: %d\n", getppid());
    }


    return 0;
}