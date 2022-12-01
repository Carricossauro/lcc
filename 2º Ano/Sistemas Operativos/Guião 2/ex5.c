#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int status;

    for (int i = 0; i < 10; i++) {
        if (pid = fork() == 0) {
            printf("Filho criado:\n");
            printf("Pid do próprio: %d\n", getpid());
            printf("Pid do pai: %d\n", getppid());
        } else {
            pid = wait(&status);
            _exit(0);
        }
    }


    return 0;
}