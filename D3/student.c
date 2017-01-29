#include "student.h"

#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "queue.h"
#include "state.h"
#include "util.h"

struct student* newStudent(char* name) {
    struct student* s = (struct student*)malloc(sizeof(struct student));

    memset(s, 0, sizeof(s));
    s->name = name;
    s->status = WORKING;

    return s;
}

void studentExecute(struct student* this, struct state* state) {
    char timebuf[11];

    while(1) {
        if(this->status == WORKING) {
            printf("[%s] %s is going to work.\n", gen_time(timebuf), this->name);

            // work for a bit
            sleep(rand() % 64 + 16);

            // try to get into the queue
            printf("[%s] %s needs some help and is going to the TA's office.\n", gen_time(timebuf), this->name);
            if(enqueue(state->queue, this)) {
                this->status = WAITING;
            }
            else {
                printf("[%s] %s could not get into the queue as it is full.\n", gen_time(timebuf), this->name);
            }
        }

        else if(this->status == WAITING) {
            if(head(state->queue) == this && state->ta->status == SLEEPING) {
                // wake the lazy ass up
                printf("[%s] The TA is sleeping; looks like %s will have to wake that lazy ass up.\n", gen_time(timebuf), this->name);
                state->ta->status = HELPING;
                sem_post(&state->ta->semaphore);
            }

            sleep(1);
        }

        // no action if CONSULTING, the TA thread takes care of it
    }
}

void* studentThread(void* arg) {
    struct student_thread_arg* data = (struct student_thread_arg*)arg;
    studentExecute(data->student, data->state);

    free(data);
    return NULL;
}

void destroyStudent(struct student* this) {
    if(this != NULL) {
        free(this);
    }
}
