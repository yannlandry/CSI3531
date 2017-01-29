#ifndef TA_H
#define TA_H

#include <semaphore.h>

#include "state.h"
#include "student.h"

struct ta {
    enum {SLEEPING, HELPING} status;
    struct student* student;
    sem_t semaphore;
};

struct ta* newTA();

void* taThread(void* arg);

void destroyTA(struct ta* this);

#endif
