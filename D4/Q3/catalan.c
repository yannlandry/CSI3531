#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "catalan.h"

uint64_t factorial(int n) {
	uint64_t fact = 1;
	for(; n > 0; --n) {
		fact*= n;
	}
	return fact;
}

int max_factors(int n) {
	return log2(n);
}

void decompose(int n, int* array, int* offset) {
	for(int i = 2; i <= n/2; ++i) {
		while(n % i == 0) {
			array[(*offset)++] = i;
			n/= i;
		}
	}

	if(n > 1) {
		array[(*offset)++] = n;
	}
}

int compare(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

// We couldn't just do the formula because 2n! would have caused overflow,
// even on uint64_t, so we decompose everything into factors that get cancelled out
uint64_t catalan(int n) {
	// works for smaller values
	if(n < 12) {
		return factorial(2*n) / factorial(n+1) / factorial(n);
	}

	// 2n! / (n+1)! / n
	int a = 2*n, b = n+1, c = n;

	// using a, find max factors for every number 2-a
	int mulfact = 0;
	for(int i = 2; i <= a; ++i) {
		mulfact+= max_factors(i);
	}

	// create array of multiplier factors
	int* multipliers = (int*)malloc(mulfact * sizeof(int));

	// decompose each number 2-a into array
	mulfact = 0;
	for(int i = 2; i <= a; ++i) {
		decompose(i, multipliers, &mulfact);
	}
	multipliers = (int*)realloc(multipliers, mulfact * sizeof(int));

	// using c, find max factors 2-c, twice
	// and max factors for b
	int divfact = 0;
	for(int i = 2; i <= c; ++i) {
		divfact+= max_factors(i);
	}
	divfact*= 2;
	divfact+= max_factors(b);

	// create array of divider factors
	int* dividers = (int*)malloc(divfact * sizeof(int));

	// decompose each number 2-c into array, twice
	// and decompose b
	divfact = 0;
	for(int i = 2; i <= c; ++i) {
		decompose(i, dividers, &divfact);
		decompose(i, dividers, &divfact);
	}
	decompose(b, dividers, &divfact);
	dividers = (int*)realloc(dividers, divfact * sizeof(int));

	// sort both arrays
	qsort(multipliers, mulfact, sizeof(int), compare);
	qsort(dividers, divfact, sizeof(int), compare);

	// go through both arrays and eliminate
	// add numbers that cannot be eliminated to dividend and divisor
	int mulit = 0, divit = 0;
	uint64_t dividend = 1, divisor = 1;

	while(mulit < mulfact && divit < divfact) {
		if(multipliers[mulit] == dividers[divit]) {
			// cancel them out
			multipliers[mulit++] = 0;
			dividers[divit++] = 0;
		}
		else if(multipliers[mulit] > dividers[divit]) {
			divisor*= dividers[divit++];
		}
		else if(multipliers[mulit] < dividers[divit]) {
			dividend*= multipliers[mulit++];
		}
	}

	// add remaining values to dividend and divisor
	while(mulit < mulfact) {
		dividend*= multipliers[mulit++];
	}
	while(divit < divfact) {
		divisor*= dividers[divit++];
	}

	// clean the mess
	free(multipliers);
	free(dividers);

	// here we go
	return dividend / divisor;
}
