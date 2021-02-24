#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define MAXBUFFER 1

// Ex 1 -> mycp
int main(int argc, char *argv[]) {
	if (argc >= 3) {
		int fileToRead = open(argv[1], O_RDONLY);

		if (fileToRead == -1) {
			perror("Open");
			return -1;
		}

		int fileToWrite = open(argv[2], O_CREAT | O_RDWR, 0600);

		ssize_t res = 1;
		char buffer[MAXBUFFER];
		while(res != 0) {
			res = read(fileToRead, &buffer, MAXBUFFER);
			if (res == 0) break;
			res = write(fileToWrite, &buffer, MAXBUFFER);
		}
		close(fileToWrite);
		close(fileToRead);
	}
	return 0;
}
