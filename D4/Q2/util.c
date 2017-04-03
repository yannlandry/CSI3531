#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RAND_STR_LEN 20

char* get_refstr(int argc, char* argv[]) {
	char* refstr = 0;

	// work with user-provided string
	if(argc > 1) {
		int len = strlen(argv[1]);
		refstr = (char*)malloc(len + 1);
		strcpy(refstr, argv[1]);

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

		// allocate, random-fill, terminate
		refstr = (char*)malloc(RAND_STR_LEN + 1);
		for(int i = 0; i < RAND_STR_LEN; ++i) {
			refstr[i] = rand() % 10 + '0';
		}
		refstr[RAND_STR_LEN] = 0;

		printf("No page-reference string provided, so one was randomly generated: %s\n", refstr);
	}

	return refstr;
}
