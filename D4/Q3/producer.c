#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include "shared_block.h"

int factorial(int n) {
	int fact = 1;
	for(; n > 0; --n) {
		fact*= n;
	}
	return fact;
}

int catalan(int n) {
	return factorial(2*n) / factorial(n+1) / factorial(n);
}

int main(int argc, char* argv[]) {
	// perform validation and shit
	if(argc != 2) {
		fprintf(stderr, "USAGE:\t%s <number>\n\twhere <number> is the number of Catalan numbers to generate\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int num = atoi(argv[1]);
	if(num < 1) {
		fprintf(stderr, "Must generate at least one Catalan number.\n");
		exit(EXIT_FAILURE);
	}

	struct shared_block write = make_writable_block("tmp", num * sizeof(int));
	int* sequence = (int*)write.data;

	for(int i = 1; i <= num; ++i) {
		sequence[i-1] = catalan(i);
	}

	printf("Production finished\n");
	printf("Press any key to continue...");
	getchar();

	return 0;
}
