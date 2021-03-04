#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#define MAXBUFFER 1000

ssize_t readln(int fd, char *line, ssize_t size) {
	ssize_t res = 0;
	int j = 0;
	char local[MAXBUFFER];

	while ((res = read(fd, local, size)) > 0) {
		for(int i = 0; i < res; i++) {
			if ((char) local[i] != '\n') {
				line[j++] = local[i];
			} else return j;
		}
	}

	return j;
}

// Isto é um bocado estúpido mas funciona
int numbers(char *buffer, int num) {
    char local[MAXBUFFER];
    int i=0, j=0, resto;
    do {
        local[i++] = (num % 10) + 48;
        num/=10;
    } while (num != 0);
    while (i >= 0) {
        buffer[j++] = local[--i];
    }
    buffer[j++] = '.';
    buffer[j++] = ' ';
    return j;
}

int main(int argc, char *argv[]) {
	if (argc >= 2) {
		int linha = 1;
		int numSize, fd = open(argv[1], O_RDONLY);
		int endFile = lseek(fd,0,SEEK_END);
		lseek(fd, 0, SEEK_SET);
		char buffer[MAXBUFFER];
		char num[MAXBUFFER];
		ssize_t size, total = 0;

		while ((size = readln(fd, buffer, 100)) > 0 || (total + linha) < endFile) {
			total += size;
			numSize = numbers(num, linha);
			write(1, "\t",1);
			write(1, num, numSize);
			write(1, buffer,size);
			write(1, "\n",1);
			lseek(fd, total+linha, SEEK_SET);
			linha++;
		}
		close(fd);
	}
	return 0;
}
