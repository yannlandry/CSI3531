#ifndef STATE_H
#define STATE_H

#include "queue.h"
#include "student.h"
#include "ta.h"

struct state {
    struct queue* queue;
    struct ta* ta;
    struct student** students;
    int num_students;
};

struct state* newState();

void destroyState(struct state* this);

#endif
