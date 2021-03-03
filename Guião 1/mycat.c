#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#define MAXBUFFER 10

// Ex 2 -> mycat
int main() {
	ssize_t res;
	char buffer[MAXBUFFER];
	while((res = read(0, &buffer, MAXBUFFER)) != 0) {
		res = write(1, &buffer, res);
	}
	return 0;
}