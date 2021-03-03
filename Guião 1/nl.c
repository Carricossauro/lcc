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

// This is incomplete btw
int main(int argc, char *argv[]) {
	if (argc >= 2) {
		int linha = 1;
		int fd = open(argv[1], O_RDONLY);
		char buffer[MAXBUFFER];
		ssize_t size, total = 0;

		while ((size = readln(fd, buffer, 100)) > 0) {
			total += size;
			write(1, "\t",1);
			write(1, buffer,size);
			write(1, "\n",1);
			lseek(fd, total+linha, SEEK_SET);
			linha++;
		}
	}
	return 0;
}
