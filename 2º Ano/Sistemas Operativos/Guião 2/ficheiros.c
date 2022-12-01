#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>
#include<fcntl.h>

int main() {
    ssize_t res=0;
    int fd, pid, status;
    char buff;

    fd = open("teste.txt", O_CREAT | O_RDWR, 0666);
    res = write(fd, "abcd", 4);

    if (pid = fork() == 0) {
        res = write(fd, "efghij", 6);
        _exit(res);
    } else {
        res = wait(&status);
        lseek(fd, -WEXITSTATUS(status), SEEK_CUR);

        while (res = read(fd, &buff, 1))
        {
            write(1,&buff,1);
        }
        

    }
    write(1,"\n",1);
    close(fd);
    int i = unlink("teste.txt");
    return 0;
}