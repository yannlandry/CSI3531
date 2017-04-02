#include <stdio.h>
#include <string.h>
#include <time.h>

#include "minheap.h"
#include "page.h"

#define RAND_STR_LEN 20
#define PHYS_MEM_SZ 5

int min(int a, int b) {
	return a < b ? a : b;
}

// returns 1 if there was a page fault
int request_page(int id, struct page* table, struct heap* entrances, int time) {
	// it's there, no page fault
	if(table[id].present) {
		return 0;
	}
	// otherwise bring it from memory

	// if physical memory is full, find next page to remove, remove it
	if(entrances->count == PHYS_MEM_SZ) {
		int removed = heap_pop(entrances)->id;
		table[removed].present = 0;

		// only display a PF if replacing another page, because at the beginning
		// no pages are in primary memory and we don't want to start with a bunch
		// of page faults
		printf("PAGE FAULT: Page %d was not present in the primary memory; it will replace page %d.\n", id, removed);
	}

	// send page to primary memory, put into heap
	table[id].present = 1;
	table[id].entered = time;
	heap_push(entrances, &table[id]);

	return 1;
}

int main(int argc, char* argv[]) {
	const char* refstr = 0;

	// work with user-provided string
	if(argc > 1) {
		refstr = argv[1];
		int len = strlen(refstr);

		for(int i = 0; i < len; ++i) {
			if(refstr[i] < '0' || refstr[i] > '9') {
				fprintf(stderr, "Please provide a string made of only numeric characters.\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	// or generate one
	else {
		srand(time(NULL));

		char ref[RAND_STR_LEN];
		for(int i = 0; i < RAND_STR_LEN; ++i) {
			ref[i] = rand() % 10 + '0';
		}

		refstr = ref;
		printf("No page-reference string provided, so one was randomly generated: %s\n", refstr);
	}

	struct page table[10];
	for(int i = 0; i < 10; ++i) {
		table[i] = new_page(i);
	}

	struct heap entrances = new_heap();
	int faults = 0;

	int len = strlen(refstr);
	for(int i = 0; i < len; ++i) {
		faults+= request_page(refstr[i] - '0', table, &entrances, i);
	}

	// none of the pages were in the primary memory at the beginning,
	// so we offset the memory size to obtain a more accurate count
	faults-= min(entrances.count, PHYS_MEM_SZ);
	printf("There were %d page faults.\n", faults);

	return 0;
}
