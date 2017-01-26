#include "ta.h"

#include <stdio.h>
#include <string.h>

#include "state.h"

struct ta* newTA() {
    struct ta* t = (struct ta*)malloc(sizeof(struct ta));

    memset(t, 0, sizeof(struct ta));
    t->sleeping = 0;

    return t;
}

void execute(struct state* state) {
    // logic for a TA
    printf("Would execute the TA.\n");
}

void* taThread(void* arg) {
    struct state* state = (struct state*)arg;
    execute(state);

    return NULL;
}
