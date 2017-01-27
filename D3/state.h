#ifndef STATE_H
#define STATE_H

#include "queue.h"
#include "student.h"
#include "ta.h"

struct state {
    struct queue* queue;
    struct student** students;
    struct ta* ta;
};

struct state* newState();

#endif
