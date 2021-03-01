#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

// Ex 3
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


/*
// Ex 4
ssize_t readln(int fd, char *line, size_t size) {
	char c[50];
	size = 0;
	int i = 0;
	ssize_t res = 1;
	while (res) {
		res = read(fd, &c, 50);
		for (i=0; i < res; i++,size++) {
			if (c[i] == '\n') {
				line[size++] = '\0';
				res = 0;
				break;
			}
			line[size] = c[i];
		}
	}
	return size;
}
*/

int main() {
	char line[100];
	ssize_t size;
	int fd = open("ola.txt", O_RDONLY);
	size = readln(fd, line, size);
	write(1, &line, size);
	close(fd);
	return 0;
}
