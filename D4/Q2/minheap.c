/*
	minheap.h: adapted from max-heap implementation by Aatish Neupane
	at https://gist.github.com/aatishnn/8265656
*/

#include "minheap.h"

#include <stdio.h>
#include <stdlib.h>

#include "page.h"

struct heap new_heap() {
	struct heap h;
	h.count = 0;
	h.size = INITIAL_SIZE;
	h.heaparr = (struct page**)malloc(sizeof(struct page*) * h.size);
}

void min_heapify(struct page** data, int loc, int count) {
	int left, right, smallest;
	left = 2*(loc) + 1;
	right = left + 1;
	smallest = loc;

	if (left <= count && data[left]->entered < data[smallest]->entered) {
		smallest = left;
	}
	if (right <= count && data[right]->entered < data[smallest]->entered) {
		smallest = right;
	}

	if(smallest != loc) {
		struct page* temp = data[loc];
		data[loc] = data[smallest];
		data[smallest] = temp;
		min_heapify(data, smallest, count);
	}
}

void heap_push(struct heap* h, struct page* value) {
	// Resize the heap if it is too small to hold all the data
	if (h->count == h->size) {
		h->size*= ENLARGEMENT_FACTOR;
		h->heaparr = realloc(h->heaparr, sizeof(struct page*) * h->size);
	}

	int index = h->count++; // First insert at last of array
	int parent;

	// Find out where to put the element and put it
	for(;index; index = parent) {
		parent = (index - 1) / 2;
		if(h->heaparr[parent]->entered <= value->entered) break;
		h->heaparr[index] = h->heaparr[parent];
	}
	h->heaparr[index] = value;
}

struct page* heap_pop(struct heap* h) {
	struct page* temp = h->heaparr[--h->count];

	if(h->count <= h->size / ENLARGEMENT_FACTOR && h->size > INITIAL_SIZE) {
		h->size/= ENLARGEMENT_FACTOR;
		h->heaparr = realloc(h->heaparr, sizeof(struct page*) * h->size);
	}

	struct page* removed = h->heaparr[0];
	h->heaparr[0] = temp;
	min_heapify(h->heaparr, 0, h->count);

	return removed;
}
