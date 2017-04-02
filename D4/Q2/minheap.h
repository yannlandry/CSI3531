#ifndef MINHEAP_H
#define MINHEAP_H

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 8
#define ENLARGEMENT_FACTOR 2

struct heap {
	int size;
	int count;
	struct page** heaparr;
};

struct heap new_heap();

void heap_push(struct heap* h, struct page* value);

struct page* heap_pop(struct heap* h);

#endif
