#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int esc = open("fifo", O_WRONLY);
    char buffer;

    while (read(0, &buffer, 1)) write(esc, &buffer, 1);

    unlink("fifo");

    return 0;
}