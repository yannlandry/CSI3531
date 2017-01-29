#include "state.h"

#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "student.h"
#include "ta.h"

struct state* newState() {
    struct state* s = (struct state*)malloc(sizeof(struct state));
    memset(s, 0, sizeof(struct state));
    return s;
}

void destroyState(struct state* this) {
    if(this != NULL) {
        destroyTA(this->ta);
        destroyQueue(this->queue);

        if(this->students != NULL) {
            for(int i = 0; i < this->num_students; ++i) {
                destroyStudent(this->students[i]);
            }
            free(this->students);
        }

        free(this);
    }
}
