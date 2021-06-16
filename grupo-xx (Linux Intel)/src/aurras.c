#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAXBUFFER 50

void reverse(char s[]) {
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[]){
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void term_handler() {
    char pid[MAXBUFFER];
    itoa(getpid(), pid);

    char pid_escrever[strlen(pid)+5];
    strcpy(pid_escrever, "tmp/w");
    strcpy(pid_escrever+5,pid);

    char pid_ler[strlen(pid)+5];
    strcpy(pid_escrever, "tmp/r");
    strcpy(pid_escrever+5,pid);

    unlink(pid_ler);
    unlink(pid_escrever);
    _exit(0);
}

void status() {
    char pid[MAXBUFFER];
    itoa(getpid(), pid);

    char pid_escrever[strlen(pid)+5];
    strcpy(pid_escrever, "tmp/w");
    strcpy(pid_escrever+5,pid);

    char pid_ler[strlen(pid)+5];
    strcpy(pid_ler, "tmp/r");
    strcpy(pid_ler+5,pid);

    if (mkfifo(pid_ler, 0666) == 0 && mkfifo(pid_escrever, 0666) == 0) {
        if (signal(SIGINT, term_handler) == SIG_ERR) {
                unlink(pid_ler);
                unlink(pid_escrever);
                perror("Signal1");
                _exit(-1);
        }
        if (signal(SIGTERM, term_handler) == SIG_ERR) {
                unlink(pid_ler);
                unlink(pid_escrever);
                perror("Signal2");
                _exit(-1);
        }

        int pipePrincipal = open("tmp/main", O_WRONLY);

        if (pipePrincipal == -1) {
            perror("Erro ao abrir pipe");
            unlink(pid_ler);
            unlink(pid_escrever);
            _exit(-1);
        }

        for (int i = 0; i < strlen(pid); i++)
            write(pipePrincipal, pid+i, 1);
        close(pipePrincipal);

        int pipe_escrever = open(pid_escrever, O_WRONLY);

        if (pipe_escrever == -1) {
            perror("Erro ao abrir pipe");
            unlink(pid_ler);
            unlink(pid_escrever);
            _exit(-1);
        }

        write(pipe_escrever, "status", 6);
        close(pipe_escrever);

        char buffer;
        int pipe_ler = open(pid_ler, O_RDONLY);

        if (pipe_ler == -1) {
            perror("Erro ao abrir pipe");
            unlink(pid_ler);
            unlink(pid_escrever);
            _exit(-1);
        }

        while (read(pipe_ler, &buffer, 1) > 0) write(1, &buffer, 1);

        close(pipe_ler);
        unlink(pid_ler);
        unlink(pid_escrever);
    } else {
        perror("Mkfifo");
        _exit(-1);
    }
}

void usr1_handler(int signum) {
    write(1, "processing\n", 11);
}

void usr2_handler(int signum) {
    char pid[MAXBUFFER];
    itoa(getpid(), pid);
    char pid_escrever[strlen(pid)+5];
    strcpy(pid_escrever, "tmp/w");
    strcpy(pid_escrever+5,pid);

    unlink(pid_escrever);
    _exit(0);
}

void transform(int argc, char **argv) {
    char pid[MAXBUFFER];
    itoa(getpid(), pid);
    char pid_escrever[strlen(pid)+5];
    strcpy(pid_escrever, "tmp/w");
    strcpy(pid_escrever+5,pid);

    if (mkfifo(pid_escrever, 0666) == 0) {
        if (signal(SIGINT, usr2_handler) == SIG_ERR || signal(SIGTERM, usr2_handler) == SIG_ERR) {
                unlink(pid_escrever);
                perror("Signal");
                _exit(-1);
        }

        int pipePrincipal = open("tmp/main", O_WRONLY);

        if (pipePrincipal == -1) {
            perror("Erro ao abrir pipe");
            unlink(pid_escrever);
            _exit(-1);
        }

        write(pipePrincipal, pid, strlen(pid));
        close(pipePrincipal);

        int pipe_escrever = open(pid_escrever, O_WRONLY);

        if (pipe_escrever == -1) {
            perror("Erro ao abrir pipe");
            unlink(pid_escrever);
            _exit(-1);
        }

        for (int i = 1; i < argc; i++) {
            write(pipe_escrever, argv[i], strlen(argv[i]));
            write(pipe_escrever, ";", 1); // transform( ͡° ͜ʖ ͡°)samples sample-1.m4a( ͡° ͜ʖ ͡°)output.m4a alto eco rapido
        }
        close(pipe_escrever);
        unlink(pid_escrever);

        if (signal(SIGUSR1, usr1_handler) == SIG_ERR || signal(SIGUSR2, usr2_handler) == SIG_ERR) {
            perror("Signal");
            unlink(pid_escrever);
            _exit(-1);
        }

        write(1, "pending\n", 8);

        while(1) pause();
    } else {
        perror("Mkfifo");
        _exit(-1);
    }
}

int main(int argc, char **argv) {
    if (argc >= 2 && !strcmp(argv[1], "status")) {
        status();
    } else if (argc >= 5 && !strcmp(argv[1], "transform")) {
        transform(argc, argv);
    } else {
        write(1,"./aurras status\n", 16);
        write(1,"./aurras transform input-filename output-filename filter-id-1 filter-id-2 ...\n",78);
    }
    return 0;
}