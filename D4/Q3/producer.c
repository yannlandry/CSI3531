#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include "catalan.h"

#include "shared_block.h"

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
	if(num > 36) {
		num = 36;
		printf("Production will be limited to 36 as unsigned 64-bit integers cannot support Catalan numbers beyond the value at 36.\n");
	}

	// make shared memory block
	struct shared_block write = make_writable_block("tmp", num * sizeof(uint64_t));
	uint64_t* sequence = (uint64_t*)write.data;

	// generate and write to memory
	for(int i = 0; i < num; ++i) {
		sequence[i] = catalan(i);
		printf("%lld ", (unsigned long long)sequence[i]);
	}
	printf("\n");

	printf("Production finished\n");
	printf("Press any key to continue...");
	getchar();

	destroy_writable_block(write);

	return 0;
}
