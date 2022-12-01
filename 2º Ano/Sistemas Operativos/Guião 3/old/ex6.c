#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<fcntl.h>

int system(char **argv) {
    if (argv[1] == NULL) return 1;
    
    if (fork() == 0) {
        execvp(argv[1], argv+1);
        
        _exit(127);
    }

    int status;
    pid_t pid = wait(&status);
    return status;
}

int main(int argc, char **argv) {

    system(argv);

    return 0;
}