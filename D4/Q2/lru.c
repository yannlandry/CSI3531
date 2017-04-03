#include <stdio.h>
#include <string.h>

#include "minheap.h"
#include "page.h"
#include "util.h"

#define PHYS_MEM_SZ 5

// keep track of # of pages in primary memory
int count = 0;

int min(int a, int b) {
	return a < b ? a : b;
}

// returns 1 if there was a page fault
int request_page(int id, struct page* table, int time) {
	// set use time
	table[id].used = time;

	// it's there, no page fault
	if(table[id].present) {
		return 0;
	}
	// otherwise bring it from memory

	// if physical memory is full, find next page to remove, remove it
	if(count == PHYS_MEM_SZ) {
		// find page here
		// lru = least recent use
		int lru = time, removed = 0;
		for(int i = 0; i < 10; ++i) {
			if(table[i].present && table[i].used < lru) {
				lru = table[i].used;
				removed = i;
			}
		}

		table[removed].present = 0;
		--count;

		// only display a PF if replacing another page, because at the beginning
		// no pages are in primary memory and we don't want to start with a bunch
		// of page faults
		printf("PAGE FAULT: Page %d was not present in the primary memory; it will replace page %d.\n", id, removed);
	}

	// send page to primary memory, put into heap
	table[id].present = 1;
	++count;

	return 1;
}

int main(int argc, char* argv[]) {
	char* refstr = get_refstr(argc, argv);

	// table to hold pages
	struct page table[10];
	for(int i = 0; i < 10; ++i) {
		table[i] = new_page(i);
	}

	int faults = 0;

	// run page-replacement simulation
	int len = strlen(refstr);
	for(int i = 0; i < len; ++i) {
		faults+= request_page(refstr[i] - '0', table, i);
	}

	// none of the pages were in the primary memory at the beginning,
	// so we offset the memory size to obtain a more accurate count
	faults-= min(count, PHYS_MEM_SZ);
	printf("There were %d page faults.\n", faults);

	// clean up
	free(refstr);

	return 0;
}
