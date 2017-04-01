#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include "shared_block.h"

int main(int argc, char* argv[]) {
	struct shared_block read = make_readable_block("tmp");
	int* sequence = (int*)read.data;

	int size = read.size / sizeof(int);
	for(int i = 0; i < size; ++i) {
		printf("%d ", sequence[i]);
	}

	printf("\n");

	return 0;
}
