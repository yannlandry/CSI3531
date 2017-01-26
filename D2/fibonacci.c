#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct fib_attr {
    int num;
    int* gen;
};

void* fibonacci(void* arg) {
    struct fib_attr* attr = (struct fib_attr*)arg;

    int number = attr->num;
    int* generated = attr->gen;

    // fill initial
    for(int i = 0; i < 2 && i < number; ++i) {
        generated[i] = i;
    }

    // compute the rest
    for(int i = 2; i < number; ++i) {
        generated[i] = generated[i-1] + generated[i-2];
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    // do some validation
    if(argc != 2) {
        fprintf(stderr, "Usage: primes <num>\n<num>: Number until which to generate primes.\n");
        return 1;
    }

    int num = atoi(argv[1]);
    if(num < 1) {
        fprintf(stderr, "Error: Please enter an integer equal or greater to 1 as argument.\n");
        return 1;
    }

    // set parameters
    struct fib_attr attr;
    attr.num = num;
    attr.gen = malloc(sizeof(int) * num);

    // create thread
    pthread_t thread;
    int result = pthread_create(&thread, NULL, fibonacci, &attr);
    if(result != 0) {
        fprintf(stderr, "Error creating thread.\n");
    }

    // join thread
    result = pthread_join(thread, NULL);
    if(result != 0) {
        fprintf(stderr, "Error joining thread.\n");
    }

    printf("Sequence generated:");
    for(int i = 0; i < attr.num; ++i) {
        printf(" %d", attr.gen[i]);
    }
    printf("\n");

    free(attr.gen);

    return 0;
}
