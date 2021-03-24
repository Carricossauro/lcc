#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>
#include<fcntl.h>

int main() {
    int ret;
    int status;

    char *exec_args[] = {"ls", "-la", NULL};

    if (fork() == 0) {
        //ret = execl("/bin/ls","ls","-la", NULL);
        //ret = execlp("ls","ls","-la", NULL);
        //ret = execv("/bin/ls", exec_args);
        ret = execvp("ls",exec_args);

        printf("[Processo filho #%d]", getpid());
        perror("Error");
        _exit(ret);
    } else {
        pid_t pid = wait(&status);
    }
    return 0;
}