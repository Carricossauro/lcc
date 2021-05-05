#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    if (mkfifo("ex2", 0666) == -1) return -1;
    
    int file = open("log", O_CREAT | O_WRONLY, 0666);
    int re = open("ex2", O_RDONLY);
    char buffer;

    if (file != -1) {
        while (read(re, &buffer, 1)) write(file, &buffer, 1);
        close(file);
    }
    
    unlink("ex2");
    return 0;
}