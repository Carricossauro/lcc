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

typedef struct tasks {
    char *comando;
    char **nomes_filtros;
    int numero;
    struct tasks *prox;
} *Task;

Filtro filtros;
Task tasks;
char *pasta_filtros;

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

char** removeTask(int num) {
    char **nomes_filtros = NULL;
    Task iterador = tasks;
    Task ant = NULL;

    while (iterador != NULL && iterador->numero != num) {
        ant = iterador;
        iterador = iterador->prox;
    }

    if (iterador != NULL) {
        if (ant == NULL) {
            tasks = iterador->prox;
        } else {
            ant->prox = iterador->prox;
        }
        nomes_filtros = iterador->nomes_filtros;
        free(iterador);
    }
    return nomes_filtros;
}

void removeFiltro(char nome_filtro) {
    Filtro iterador = filtros;

    while (iterador != NULL && !strcmp(iterador->nome_filtro, nome_filtro)) iterador = iterador->prox;

    if (iterador != NULL) {
        if (iterador->atual > 0) (iterador->atual)--;
    }
}

void usr1_handler(int signum) {
    int pipe = open("close", O_RDONLY);

    if (pipe > 0) {
        char num_string[MAXBUFFER];
        while (read(pipe,num_string,1) > 0);

        int num = atoi(num_string);
        char **nomes_filtros = removeTask(num);

        int i = 0;
        while (nomes_filtros[i] != NULL) removeFiltro(nomes_filtros[i]);

        unlink("close");
    } else {
        perror("Erro ao abrir pipe");
    }
    
}

int totalFiltros() {
    Filtro iterador = filtros;
    int res = 0;

    while (iterador != NULL) {
        res += iterador->maximo;
        iterador = iterador->prox;
    }

    return res;
}

void transform(char *pid, char *info_cliente) { //transform samples/sample-1.m4a output.m4a alto eco rapido
    char *token = strtok(info_cliente, " "); // transform

    token = strtok(NULL, " "); // samples/sample-1.m4a
    char input_file[strlen(token)];
    strcpy(input_file, token);

    token = strtok(NULL, " "); // output.m4a
    char output_file[strlen(token)];
    strcpy(output_file, token);

    char *nomes_filtros[totalFiltros()]; // alto eco rapido
    int numFiltros = 0;
    token = strtok(NULL, " ");
    while (token != NULL) {
        strcpy(nomes_filtros[numFiltros++], token);
        token = strtok(NULL, " ");
    }
    nomes_filtros[numFiltros++] = NULL;

    // Falta verificar se nao ultrapassa limites de filtros
    // e ver como fazer para deixar em standby
}

int main(int argc, char **argv) {
    if (argc != 3) {
        write(1,"./aurrasd etc/aurrasd.conf bin/aurras-filters\n", 46);
        return -1;
    }

    filtros = lerConfig(argv[1]);
    pasta_filtros = argv[2];

    if (mkfifo("main", 0666) != 0) {
        perror("Mkfifo");
        return -1;
    }

    while (1) {
        fflush(stdout);
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
        info_cliente[res] = '\0';

        if (info_cliente[0] == 's') status(pid);
        else transform(pid, info_cliente);
    }

    return 0;
}