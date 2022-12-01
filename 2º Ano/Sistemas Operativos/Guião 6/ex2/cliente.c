#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    int re = open("ex2", O_WRONLY);
    char buffer;

    while (read(0, &buffer, 1)) write(re, &buffer, 1);
    
    return 0;
}