#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int i = 1;
    int status;

    if (pid = fork() == 0) {
        printf("Valor: %d\n", i);
        i++;
        _exit(0);
    } else {
        pid_t terminated = wait(&status);
    }

    printf("Valor: %d\n", i);

    i++;
    return 0;
}


/* Padrões
// 1. Filhos sequenciais

int pid, status;

for (int i = 0; i < nfilhos; i++) {
    if (pid = fork() == 0) {
        //do anything
        _exit(0);
    } else {
        pid_t terminated = wait(&status);
	    // do anything
    }
}

// 2. Filhos concorrentes

int pid, status;

for (int i = 0; i < nfilhos; i++) {
	if (pid = fork() == 0) {
	    //do anything
	    _exit(0);
	}
}

for (int i = 0; i < nfilhos; i++) {
	pid_t terminado = wait(&status);
}

// 3. Filhos em profundidade

for (int i = 0; i < nfilhos; i++) {
	if (pid = fork() == 0) {
	    //do anything
	} else {
		pid_t terminado = wait(&status);
		_exit(0);
	}
}

*/