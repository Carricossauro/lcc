#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

// abcdef ex1

int crtl_c = 0;
int segundos = 0;

void sigint_handler(int signum) {
    printf("\nCrtl+C pressionado\n");
    printf("Passados %d segundos.\n", segundos);
    crtl_c++;
}

void alarm_handler(int signum) {
    segundos++;
    alarm(1);
}

void sigquit_handler(int signum) {
    printf("\nCrtl+C pressionado um total de %d vezes.\n", crtl_c);
    printf("Processo demorou %d segundos.\n", segundos);
    _exit(0);
}

int main() {
    signal(SIGINT, sigint_handler);
    signal(SIGALRM, alarm_handler);
    signal(SIGQUIT, sigquit_handler);
    alarm(1);

    while(1);

    return 0;
}