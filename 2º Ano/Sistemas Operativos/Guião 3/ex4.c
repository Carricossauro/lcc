#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[]) {
    int ret = execv("ex3", argv);

    return ret;
}