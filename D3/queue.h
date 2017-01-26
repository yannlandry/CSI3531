#ifndef QUEUE_H
#define QUEUE_H

#include "queue.h"
#include "student.h"

#define Q_MAX 3

struct queue {
    struct student* list[Q_MAX];
    int head;
    int tail;
    pthread_mutex_t mutex;
}

struct queue* newQueue();

int add(struct queue* this, struct student* s);

struct student* remove(struct queue* this);

struct student* head(struct queue* this);

#endif
