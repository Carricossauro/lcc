#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAXBUFFER 50

typedef struct lligada {
    // alto aurrasd-gain-double 2
    char *nome_filtro;
    char *nome_executavel;
    int maximo;
    int atual;
    struct lligada *prox;
} *Filtro;

ssize_t readln(int fd, char *line, ssize_t size) {
	ssize_t res = 0;
	ssize_t i = 0;
	while ((res = read(fd, &line[i], size)) > 0 && ((char) line[i] != '\n')) {
		i+=res;
	}
	return i;
}

Filtro lerConfig(char *config) {
    int fd;
    if ((fd = open(config, O_RDONLY)) < 0) {
        perror("Erro ao abrir ficheiro");
        _exit(-1);
    }
    Filtro filtros = NULL;
    Filtro temp = NULL;
    Filtro ant = NULL;

    char line[MAXBUFFER];
    char *token;
    while (readln(fd, line, 1) > 0) {
        temp = malloc(sizeof(struct lligada));
        if (filtros == NULL) filtros = temp;
        else ant->prox = temp;
        
        token = strtok(line, " ");
        temp->nome_filtro = malloc(sizeof(char) * (strlen(token)+1));
        strcpy(temp->nome_filtro, token);

        token = strtok(NULL, " ");
        temp->nome_executavel = malloc(sizeof(char) * (strlen(token)+1));
        strcpy(temp->nome_executavel, token);

        token = strtok(NULL, " ");
        temp->maximo = atoi(token);

        temp->atual = 0;
        temp->prox = NULL;

        ant = temp;
    }
    return filtros;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        write(1,"./aurrasd etc/aurrasd.conf bin/aurras-filters\n", 46);
        return -1;
    }

    Filtro filtros = lerConfig(argv[1]);

    if (mkfifo("main", 0666) != 0) {
        perror("Mkfifo");
        return -1;
    }

    while (1) {
        int pipe = open("main", O_RDONLY);
        char pid[MAXBUFFER];
        int res = 0;

        while (read(pipe, pid+res,1) > 0) {
            res++;
        }
        pid[res++] = '\0';

        char pid_ler_cliente[MAXBUFFER];
        pid_ler_cliente[0] = 'w';
        strcpy(pid_ler_cliente+1, pid);
        res = 0;
        
        char info_cliente[MAXBUFFER];
        int pipe_ler_cliente = open(pid_ler_cliente, O_RDONLY);

        while (read(pipe_ler_cliente, info_cliente+res,1) > 0){
            res++;
        }

        write(1, info_cliente, res);
    }

    return 0;
}