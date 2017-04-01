#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include "shared_block.h"

int main(int argc, char* argv[]) {
	struct shared_block read = make_readable_block("tmp");
	uint64_t* sequence = (uint64_t*)read.data;

	int size = read.size / sizeof(uint64_t);
	for(int i = 0; i < size; ++i) {
		printf("%lld ", (unsigned long long)sequence[i]);
	}

	printf("\n");

	destroy_readable_block(read);

	return 0;
}
