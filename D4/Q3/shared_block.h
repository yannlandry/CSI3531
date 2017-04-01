#ifndef SHARED_BLOCK_H
#define SHARED_BLOCK_H

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

struct shared_block {
	int file;
	int size;
	char* data;
};

void allocate(int fd, size_t len) {
	// prep buffer
	char* buf = (char*)malloc(len);
	bzero(buf, len);

	// write zero-bytes, go back
	write(fd, buf, len);
	lseek(fd, 0, SEEK_SET);

	// finish
	free(buf);
}

struct shared_block make_writable_block(const char* filename, int size) {
	// make block, compute sizes
	struct shared_block block;
	block.size = size;
	int filesize = size + sizeof(int);

	// create memory map
	block.file = open(filename, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
	allocate(block.file, filesize);

	// set information
	char* contents = mmap((caddr_t)0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, block.file, 0);
	*((int*)contents) = size;
	block.data = contents + sizeof(int);

	return block;
}

struct shared_block make_readable_block(const char* filename) {
	struct shared_block block;

	// open file handle
	block.file = open(filename, O_RDONLY);
	if(block.file == -1) {
		block.size = 0;
		block.data = 0;
		return block;
	}

	// get size of shared memory block
	int size = 0;
	read(block.file, &size, sizeof(int));
	lseek(block.file, -sizeof(int), SEEK_CUR);

	char* contents = mmap((caddr_t)0, size + sizeof(int), PROT_READ, MAP_SHARED, block.file, 0);
	block.size = size;
	block.data = contents + sizeof(int);

	return block;
}

#endif
