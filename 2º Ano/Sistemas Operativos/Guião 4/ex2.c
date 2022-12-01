#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    int stdin = open("/etc/passwd", O_RDONLY);
    int stdout = open("saida.txt", O_CREAT | O_WRONLY, 0666);
    int stderr = open("erros.txt", O_CREAT | O_WRONLY, 0666);
    int status;

    dup2(stdin, 0);
    dup2(stdout, 1);
    dup2(stderr, 2);

    if (fork() == 0) {
        int linhas = 10;
        char buffer;
        char linha[1024];
        int i = 0;

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
    } else {
        wait(&status);
    }

    close(stdin);
    close(stdout);
    close(stderr);
    return 0;
}