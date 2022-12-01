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
    return 0;
}