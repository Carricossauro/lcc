#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    int stdi = open("/etc/passwd", O_RDONLY);
    int stdo = open("saida.txt", O_CREAT | O_WRONLY, 0666);
    int stde = open("erros.txt", O_CREAT | O_WRONLY, 0666);

    dup2(stdi, 0);
    dup2(stdo, 1);
    dup2(stde, 2);

    int linhas = 10;
    char buffer;
    char linha[1024];
    int i = 0;
    int status;

    while (linhas-- > 0) {

        while (read(0, &buffer, 1)) {
            linha[i++] = buffer;
            if (buffer == '\n') {
                break;
            }

            write(1, linha, i);
            write(2, linha, i);

            i = 0;
        }

    }
    write(1, "\n", 1);

    if (fork() == 0) {
        char *args[] = {"wc", "saida.txt", NULL};
        execvp(args[0], args);

        perror("erro");
    } else
        wait(&status);

    write(2, "\n", 1);

    close(stdi);
    close(stdo);
    close(stde);
    return 0;
}