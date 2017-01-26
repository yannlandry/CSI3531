#include "queue.h"

#include <pthread.h>
#include <string.h>

#include "student.h"

struct queue* newQueue() {
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));

    memset(q, 0, sizeof(struct queue));
    q->head = 0;
    q->tail = 0;
    q->mutex = PTHREAD_MUTEX_INITIALIZER;

    return q;
}

// add s to the queue, return false if queue is full
int add(struct queue* this, struct student* s) {
    int added = 0;
    pthread_mutex_lock(this->mutex);

    if(this->list[this->tail] == NULL) {
        this->list[this->tail] = s;
        this->tail = (this->tail + 1) % Q_MAX;

        return 1;
    }

    pthread_mutex_unlock(this->mutex);
    return added;
}

// remove student from the queue, return NULL if queue is empty
struct student* remove(struct queue* this) {
    struct student* s = NULL;
    pthread_mutex_lock(this->mutex);

    if(this->list[this->head] != NULL) {
        s = this->list[this->head];
        this->list[this->head] = NULL;
        this->head = (this->head + 1) % Q_MAX;
    }

    pthread_mutex_unlock(mutex);
    return s;
}

// get student at front of the queue, return NULL if queue is empty
struct student* head(struct queue* this) {
    return this->list[this->head];
}
