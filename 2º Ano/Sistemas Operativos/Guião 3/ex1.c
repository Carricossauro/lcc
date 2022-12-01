#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>
#include<fcntl.h>

int main() {
    int ret;

    char *exec_args[] = {"ls", "-la", NULL};
    
    //ret = execl("/bin/ls","ls","-la", NULL);
    //ret = execlp("ls","ls","-la", NULL);
    //ret = execv("/bin/ls", exec_args);
    ret = execvp("ls",exec_args);

    printf("\nteste\n");
    perror("Error");
    return 0;
}