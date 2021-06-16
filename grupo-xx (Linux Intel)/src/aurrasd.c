#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <wait.h>

#define MAXBUFFER 150

typedef struct lligada {
    // alto aurrasd-gain-double 2
    char *nome_filtro;
    char *nome_executavel;
    int maximo;
    int atual;
    struct lligada *prox;
} *Filtro;

struct quantidade_filtro {
    char *nome_filtro;
    int utilizacoes;
};

typedef struct tasks {
    char *comando;
    char **ordem_filtros;
    struct quantidade_filtro *nomes_filtros;
    int numero;
    int processamento; // 0 - a espera; 1 - a processar
    int pid;
    char *input_file;
    char *output_file;
    struct tasks *prox;
} *Task;

void monitor(Task task);
int numeroFiltros();
void status(char *pid);
void execs(int input, int output, Task task);
int disponivel(struct quantidade_filtro *nomes_filtros, int num_filtros);

Filtro filtros;
Task tasks = NULL;
char *pasta_filtros;
int numero_tasks = 0;

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

struct quantidade_filtro *removeTask(int num) {
    struct quantidade_filtro *nomes_filtros = NULL;
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

void removeFiltro(char *nome_filtro, int quantidade) {
    Filtro iterador = filtros;

    while (iterador != NULL && strcmp(iterador->nome_filtro, nome_filtro)) iterador = iterador->prox;

    if (iterador != NULL) {
        if (iterador->atual >= quantidade) (iterador->atual)-= quantidade;
    }
}

void adicionaFiltros(struct quantidade_filtro *nomes_filtros) {
    int i = 0;
    Filtro iterador = filtros;
    while (iterador != NULL) {
        iterador->atual += nomes_filtros[i++].utilizacoes;

        iterador = iterador->prox;
    }
}

void usr1_handler(int signum) {
    int pipe = open("close", O_RDONLY);

    if (pipe > 0) {
        char num_string[MAXBUFFER];
        while (read(pipe,num_string,1) > 0);

        int num = atoi(num_string);
        struct quantidade_filtro *nomes_filtros = removeTask(num);

        int i = 0;
        int num_filtros = numeroFiltros();
        for (int i = 0; i < num_filtros; i++) {
            removeFiltro(nomes_filtros[i].nome_filtro, nomes_filtros[i].utilizacoes);
        }

        unlink("close");

        Task iterador = tasks;
        while (iterador != NULL && iterador->processamento == 1) iterador=iterador->prox;
        if (iterador != NULL) {
            int disponibilidade = disponivel(nomes_filtros, num_filtros);
            if (disponibilidade == 1) {
                iterador->processamento = 1;
                int f = fork();
                if (f != -1) {
                    if (f == 0) {
                        signal(SIGINT, SIG_IGN);
                        signal(SIGTERM, SIG_IGN);
                        monitor(iterador);
                        _exit(0);
                    } else {
                        adicionaFiltros(iterador->nomes_filtros);
                    }
                } else {
                    perror("Fork");
                }
            }
        }
    } else {
        perror("Erro ao abrir pipe");
    }
    
}

int numeroFiltros() {
    Filtro iterador = filtros;
    int res = 0;

    while (iterador != NULL) {
        res++;
        iterador = iterador->prox;
    }

    return res;
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

int disponivel(struct quantidade_filtro *nomes_filtros, int num_filtros) {
    Filtro iterador = filtros;
    for (int i = 0; i < num_filtros; i++, iterador = iterador->prox) {
        if (nomes_filtros[i].utilizacoes > iterador->maximo) return -1;
        if (nomes_filtros[i].utilizacoes + iterador->atual > iterador->maximo) return 0;
    }
    return 1;
}

void inicializarArray(struct quantidade_filtro *nomes_filtros, int num_filtros) {
    Filtro iterador = filtros;
    for (int i = 0; i < num_filtros; i++, iterador = iterador->prox) {
        nomes_filtros[i].nome_filtro = iterador->nome_filtro;
        nomes_filtros[i].utilizacoes = 0;
    }
}

void transform(char *pid, char *info_cliente) { //transform samples/sample-1.m4a output.m4a alto eco rapido
    char *info_cliente_backup = malloc(sizeof(char) * strlen(info_cliente));
    strcpy(info_cliente_backup, info_cliente);

    char *token = strtok(info_cliente, "«"); // transform

    token = strtok(NULL, "«"); // samples/sample-1.m4a
    char *input_file = malloc(sizeof(char) * strlen(token));
    strcpy(input_file, token);

    token = strtok(NULL, "«"); // output.m4a
    char *output_file = malloc(sizeof(char) * strlen(token));
    strcpy(output_file, token);

    int numFiltros = numeroFiltros();
    struct quantidade_filtro *nomes_filtros = malloc(sizeof(struct quantidade_filtro) * numFiltros); // alto eco rapido
    inicializarArray(nomes_filtros, numFiltros);

    char **ordem_filtros = malloc(sizeof(char*) * (totalFiltros()+1));

    token = strtok(NULL, "«");
    int k = 0;
    while (token != NULL) {
        ordem_filtros[k] = malloc(sizeof(char) * strlen(token));
        strcpy(ordem_filtros[k++], token);
        for (int i = 0; i < numFiltros; i++) {
            if (!strcmp(nomes_filtros[i].nome_filtro, token)) {
                nomes_filtros[i].utilizacoes++;
                break;
            }
        }
        token = strtok(NULL, "«");
    }
    ordem_filtros[k++] = NULL;

    int disponibilidade = disponivel(nomes_filtros, numFiltros);

    if (disponibilidade == -1) {
        write(1,"Limite de filtros excedido\n",27);
        kill(atoi(pid), SIGUSR2);
    } else {
        Task temp = malloc(sizeof(struct tasks));
        temp->comando = malloc(sizeof(char) * strlen(info_cliente_backup));
        strcpy(temp->comando, info_cliente_backup);
        temp->nomes_filtros = nomes_filtros;
        temp->numero = ++numero_tasks;
        temp->prox = NULL;
        temp->pid = atoi(pid);
        temp->input_file = malloc(sizeof(char) * strlen(input_file));
        strcpy(temp->input_file, input_file);
        temp->output_file = malloc(sizeof(char) * strlen(output_file));
        strcpy(temp->output_file, output_file);
        temp->ordem_filtros = ordem_filtros;

        Task iterador = tasks;
        if (iterador == NULL) {
            tasks = temp;
        } else {
            while (iterador->prox != NULL) iterador = iterador->prox;
            iterador->prox = temp;
        }

        if (disponibilidade == 1) {
            temp->processamento = 1;
            int f = fork();
            if (f != -1) {
                if (f == 0) {
                    signal(SIGINT, SIG_IGN);
                    signal(SIGTERM, SIG_IGN);
                    monitor(temp);
                    _exit(0);
                } else {
                    adicionaFiltros(temp->nomes_filtros);
                }
            } else {
                perror("Fork");
            }
        } else {
            temp->processamento = 0;
        }
    }
}

void term_handler(int signum) {
    unlink("main");

    printf("A espera para fechar\n");
    while (tasks != NULL) {
        pause();
        printf("Fechou\n");
    }

    _exit(0);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        write(1,"./aurrasd etc/aurrasd.conf bin/aurras-filters\n", 46);
        return -1;
    }

    signal(SIGUSR1, usr1_handler);
    signal(SIGTERM, term_handler);
    signal(SIGINT, term_handler);

    filtros = lerConfig(argv[1]);
    pasta_filtros = argv[2];

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
        info_cliente[res] = '\0';

        if (info_cliente[0] == 's') status(pid);
        else transform(pid, info_cliente);
    }

    return 0;
}

char *concatenarFiltro(char *executavel, char *filtro) {
    int len = strlen(pasta_filtros);
    
    executavel = malloc(sizeof(char) * (strlen(filtro) + len+2));

    strcpy(executavel, pasta_filtros); //     /bin/filtro
    executavel[len] = '/';
    

    Filtro iterador = filtros;
    while (iterador != NULL && strcmp(iterador->nome_filtro, filtro)) iterador = iterador->prox;

    strcpy(executavel+len+1, iterador->nome_executavel);
    return executavel;
}

void itoa(int value, char*buffer, int base) {
	sprintf(buffer, "%d", value);
}

void fecharFilho(Task task) {
    if (mkfifo("close", 0666) == 0) {
        kill(getppid(), SIGUSR1);
        kill(task->pid, SIGUSR2);
            
        char num[MAXBUFFER];
        itoa(task->numero, num, 10);

        int pipe = open("close", O_WRONLY);

        int i = 0;
        while (num[i] != '\0') write(pipe, num+(i++), 1);

        close(pipe);
        _exit(0);
    } else {
        perror("Mkfifo");
        _exit(-1);
    }
}

void monitor(Task task) {
    int f = fork();
    
    if (f == -1) {
        perror("Fork");
        kill(task->pid,SIGUSR2);
        fecharFilho(task);
    } else if (f == 0) {
        int input = open(task->input_file, O_RDONLY);
        int output = open(task->output_file, O_CREAT | O_TRUNC | O_WRONLY, 0777);

        if (input == -1) {
            perror("Open input");
            _exit(-1);
        }

        if (output == -1) {
            perror("Open output");
            _exit(-1);
        }

        sleep(5);
        execs(input, output, task);
        _exit(-1);
    } else {
        int status;
        kill(task->pid, SIGUSR1);

        wait(&status);
        
        fecharFilho(task);
    }
}

void execs(int input, int output, Task task) {
    int i = 0;
    int pip[2];

    while (task->ordem_filtros[i] != NULL) {
        if (i != 0) {
            dup2(pip[0],0);
            close(pip[0]);
        } else dup2(input,0);

        if (task->ordem_filtros[i+1] == NULL) dup2(output,1);
        else {
            if (pipe(pip) == 0) {
                dup2(pip[1],1);
                close(pip[1]);
            } else {
                perror("Pipe");
                _exit(-1);
            }
        }

        int f;
        if ((f = fork()) == -1) {
                perror("Fork");
                _exit(-1);
        } else if (f == 0) {
            char *executavel;
            executavel = concatenarFiltro(executavel, task->ordem_filtros[i]);
            execlp(executavel, executavel, NULL);
            perror("Exec");
            _exit(-1);
        }

        i++;
    }
}

void status(char *pid) {
    int f = fork();

    if (f == 0) {
        signal(SIGINT, SIG_IGN);
        signal(SIGTERM, SIG_IGN);

        char pid_escrever[strlen(pid)+2];
        pid_escrever[0] = 'r';
        strcpy(pid_escrever+1,pid);

        int pipe_escrever = open(pid_escrever, O_WRONLY);

        Task iterador = tasks;

        while (iterador != NULL && iterador->processamento == 1) {
            printf("%s\n", iterador->comando);
            write(pipe_escrever,iterador->comando, strlen(iterador->comando));
            write(pipe_escrever, "\n", 1);
            iterador = iterador->prox;
        }

        close(pipe_escrever);
        _exit(0);
    }
}