#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int res;
	srandom(time(NULL));
	res = random() % 3;
	return res;
}
