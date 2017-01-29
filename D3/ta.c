#include "ta.h"

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "queue.h"
#include "state.h"
#include "student.h"
#include "util.h"

struct ta* newTA() {
    struct ta* t = (struct ta*)malloc(sizeof(struct ta));

    memset(t, 0, sizeof(struct ta));
    t->status = SLEEPING;
    t->student = NULL;
    sem_init(&t->semaphore, 0, 0);

    return t;
}

void taExecute(struct state* state) {
    struct ta* this = state->ta;
    char timebuf[11];

    // master loop
    while(1) {
        // awake
        sem_wait(&this->semaphore);
        printf("[%s] The TA has been awaken and, unsurprisingly, is not the least embarrassed of his behaviour.\n", gen_time(timebuf));

        // process all students
        struct student* s;
        while( (s = dequeue(state->queue)) != NULL ) {
            s->status = CONSULTING;
            printf("[%s] The TA is now helping %s in his office.\n", gen_time(timebuf), s->name);
            sleep(rand() % 16 + 4);
            s->status = WORKING;
        }

        // go to sleep
        // sem stays locked until a student unlocks it
        printf("[%s] There are no more students waiting for help. The TA can now go back to sleep.\n", gen_time(timebuf));
        this->status = SLEEPING;
    }

    printf("[%s] All right kids, that's it for today! Your TA is tired now...\n", gen_time(timebuf));
}

void* taThread(void* arg) {
    struct state* state = (struct state*)arg;
    taExecute(state);

    return NULL;
}

void destroyTA(struct ta* this) {
    if(this != NULL) {
        sem_destroy(&this->semaphore);
        free(this);
    }
}
