#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>


struct pessoa {
    char nome[100];
    int idade;
};

int numbers(char *buffer, int num) {
    char local[20];
    int i=0, j=0;
    do {
        local[i++] = (num % 10) + 48;
        num/=10;
    } while (num != 0);
    while (i >= 0) {
        buffer[j++] = local[--i];
    }
    buffer[j] = '\0';
    return j;
}

// Exercícios 6 e 7 feitos em conjunto
int main(int argc, char *argv[]) {
    if (argc >= 4) {
        if (!strcmp(argv[1], "-i")) {
            
            int file = open("pessoas.txt", O_RDWR);
            int enc = 0;
            int reg = 1;
            char registo[20];
            ssize_t res;
            char garbage;
            struct pessoa humano;

            // Procura o nome e conta o número de registos
            while (!enc && (res = read(file, &humano, sizeof(struct pessoa))) > 0) {
                read(file, &garbage, 1);
                if (!strcmp(humano.nome, argv[2])) {
                    enc = 1;
                } else reg++;
            }
            
            // Guarda o nome e a idade no ficheiro se ainda não existir.
            // Imprime no stdout o número do registo
            if (!enc) {
                strcpy(humano.nome, argv[2]);
                humano.idade = atoi(argv[3]);
                reg = numbers(registo, reg);

                write(file, &humano, sizeof(struct pessoa));
                write(file, "\n", 1);
                write(1,"Registo ", 8);
                write(1, registo, reg);
                write(1,"\n",1);

            } else write(1, "Já existe alguém com esse nome\n", 33);

            close(file);
        }

        // Esta merda funcionou à primeira, poggers
        else if (!strcmp(argv[1], "-u")) {

            int file = open("pessoas.txt", O_RDWR);
            ssize_t res;
            int reg = 1;
            int enc = 0;
            char garbage, registo[20];
            struct pessoa humano;
            int totalLido;

            numbers(registo, reg);

            while (!enc && (res = read(file, &humano, sizeof(struct pessoa))) > 0) {
                read(file, &garbage, 1);
                totalLido += sizeof(struct pessoa) + 1;

                if (!strcmp(humano.nome, argv[2]) || !strcmp(argv[2], registo)) {
                    enc = 1;
                } else numbers(registo, ++reg);
            }

            if (enc) {
                // Voltar para o início do ficheiro para reescrever
                lseek(file, totalLido-sizeof(struct pessoa)-1, SEEK_SET);
                
                humano.idade = atoi(argv[3]);

                write(file, &humano, sizeof(struct pessoa));
                write(file, "\n",1);
            }



            close(file);
        } else write(1, "Invalid inputs\n", 15);

    } else if (argc >= 2 && strcmp(argv[1], "-a") == 0) {
        // Nao faz parte dos exercícios, era só para ir confirmando os resultados

        int file = open("pessoas.txt", O_RDONLY);
        struct pessoa humano;
        char garbage;
        char idString[20];
        ssize_t res;

        while ((res = read(file, &humano, sizeof(struct pessoa))) > 0) {
            write(1,humano.nome, strlen(humano.nome));
            write(1, " ", 1);
            res = numbers(idString, humano.idade);
            write(1, idString, res);
            read(file, &garbage, 1);
            write(1, "\n", 1);
        }

        close(file);
    } else write(1, "Invalid inputs\n", 15);
    return 0;
}