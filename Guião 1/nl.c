#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

ssize_t readln(int fd, char *line, size_t size) {
	char c;
	size = 0;
	ssize_t res;
	do {
		res = read(fd, &c, 1);
		if (res == 0) break;
		line[size++] = c;
	} while (c != '\n');
	line[--size] = '\0';
	return size;
}

// This is incomplete btw
int main(int argc, char *argv[]) {
	if (argc >= 2) {
		int numero = 1;
		char line[100];
		int fd = open(argv[1], O_RDONLY);
		ssize_t size;
		while (1) {
			if ((size = readln(fd, line, size)) > 0) {
				write(1, "\t", 1);
				write(1, line, size);
				write(1, "\n", 1);
			} else break;

		}
	}

	return 0;
}
