#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2)
        return -1;
    
    int in = -1;
    int out = -1;
    int err = -1;
    int com = 1;

    // Lê as flags (-i e -o) -> Assume que foram bem metidas
    for (int i = 1; i < argc; i+=2) {
        if (!strcmp("-i", argv[i])) {
            in = open(argv[i+1], O_RDONLY);
            dup2(in, 0);
            com += 2;
        }
        if (!strcmp("-o", argv[i])) {
            out = open(argv[i+1], O_CREAT | O_WRONLY, 0666);
            dup2(out, 1);
            com += 2;
        }
    }

    int reds = 0;
    // Lê os redirecionamentos (começa no fim e para quando não encontra nada)
    // O nome do ficheiro tem de vir colado ao sinal de redirecionamento
    for (int i = argc-2; i > 0; i--) {
        if (argv[i][0] == '>') {
            if (out != -1) close(in);

            int r = 1;
            if (argv[i][1] == '>') r++;

            out = open(argv[i]+r, O_RDONLY);

            if (r == 2) lseek(in, SEEK_END, 0);

            dup2(out, 0);
            reds++;
        } else if (argv[i][0] == '<') {
            if (in != -1) close(in);

            in = open(argv[i]+1, O_RDONLY);

            dup2(in, 0);
            reds++;
        } else if (argv[i][0] == '2' && argv[i][1] == '>') {
            int r = 2;
            if (argv[i][2] == '>') r++;

            err = open(argv[i]+r, O_CREAT | O_WRONLY, 0666);
            if (r == 3) lseek(err, SEEK_END, 0);

            dup2(err, 2);
            reds++;
        } else break;
    }
    
    if (reds != 0) {
        argv[argc-reds] = NULL;
    }

    int status;
    int pid;
    if (fork() == 0) {
        int res = execvp(argv[com], argv+com);

        perror("erro");
        _exit(res);
    } else {
        pid = wait(&status);
        printf("\nProcesso filho %d com codigo de saida %d.\n", pid, WEXITSTATUS(status));
    }

    if (in != -1) close(in);
    if (out != -1) close(out);
    if (err != -1) close(err);
    return 0;
}