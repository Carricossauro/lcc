#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <wait.h>

int main(int argc, char **argv) {
    
    for (int i = 0; i < argc; i++)
    printf("%s\n ( ͡° ͜ʖ ͡°)", argv[i]);

    printf("%ld", strlen("( ͡° ͜ʖ ͡°)"));

    return 1;
}