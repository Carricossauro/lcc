#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<time.h>

#define numberInInterval(min, max) rand()%(max-min+1)+min

// Exercício adicional incluído aqui

// ./a.out [número de linhas] [número de colunas] [número para procurar]
int main(int argc, char *argv[]) {
    pid_t pid;
    int status;
    if (argc < 4) return 1;
    
    int x = atoi(argv[3]);
    int LINHAS = atoi(argv[1]);
    int COLUNAS = atoi(argv[2]);
    int fd = open("mat.bin", O_CREAT | O_RDWR, 0666);

    // Originar matriz aleatória
    int linha[COLUNAS];
    ssize_t size = sizeof(linha);
    srand(time(NULL));
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++)
            linha[j] = numberInInterval(0,50);
        write(fd, &linha, size);
    }

    // Loop principal - Padrão de filhos sequenciais
    for (int i = 0; i < LINHAS; i++) {
        if (pid = fork() == 0) {

            lseek(fd, i*size, SEEK_SET);
            read(fd, &linha, size);

            for (int k = 0; k < COLUNAS; k++)
                if (linha[k] == x) _exit(1);
            _exit(0);

        } else {
            pid = wait(&status);
            printf("Linha %d, status: %d\n", i+1, WEXITSTATUS(status));
        }
    }

    // Mostrar resultados
    lseek(fd, 0, SEEK_SET);
    printf("Matriz era:\n");
    for (int i = 0; i < LINHAS; i++) {
        printf("%d.", i+1);
        for (int k = 0; k < COLUNAS; k++) {
            lseek(fd, i*size, SEEK_SET);
            read(fd, &linha, size);
            printf(" %d", linha[k]);
        }
        putchar('\n');
    }

    int p = unlink("mat.bin");
    return 0;
}