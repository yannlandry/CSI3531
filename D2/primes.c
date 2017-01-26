#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int is_prime(int number) {
    if(number <= 1) {
        return 0;
    }

    for (int i = 2; i*i <= number; ++i) {
        if (number % i == 0) {
            return 0;
        }
    }

    return 1;
}

void* primes(void* arg) {
    int number = *((int*)arg);

    printf("Prime numbers smaller or equal to %d:", number);
    for(int i = 1; i <= number; ++i) {
        if(is_prime(i)) {
            printf(" %d", i);
        }
    }
    printf("\n");

    return NULL;
}

int main(int argc, char* argv[]) {
    // do some validation
    if(argc != 2) {
        fprintf(stderr, "Usage: primes <num>\n<num>: Number until which to generate primes.\n");
        return 1;
    }

    int num = atoi(argv[1]);
    if(num < 2) {
        fprintf(stderr, "Error: Please enter an integer equal or greater to 2 as argument.\n");
        return 1;
    }

    // create thread
    pthread_t thread;
    int result = pthread_create(&thread, NULL, primes, &num);
    if(result != 0) {
        fprintf(stderr, "Error creating thread.\n");
    }

    // join thread
    result = pthread_join(thread, NULL);
    if(result != 0) {
        fprintf(stderr, "Error joining thread.\n");
    }

    return 0;
}
