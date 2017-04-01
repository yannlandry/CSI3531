#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include "shared_block.h"

uint64_t catalan(int n) {
	// 2n! / (n+1)! / n
	int a = 2*n, b = n+1, c = n;

	uint64_t cat = 1;
	for(; a > b; --a) {
		cat*= a;
	}
	for(; c > 1; --c) {
		cat/= c;
	}

	return cat;
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

	struct shared_block write = make_writable_block("tmp", num * sizeof(uint64_t));
	uint64_t* sequence = (uint64_t*)write.data;

	for(int i = 0; i < num; ++i) {
		sequence[i] = catalan(i);
		printf("produced %lld\n", (unsigned long long)sequence[i]);
	}

	printf("Production finished\n");
	printf("Press any key to continue...");
	getchar();

	destroy_writable_block(write);

	return 0;
}
