#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int ler = open("fifo", O_RDONLY);
    char buffer;

    while (read(ler, &buffer, 1)) write(1, &buffer, 1);

    return 0;
}