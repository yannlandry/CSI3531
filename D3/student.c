#include "student.h"

#include <string.h>

#include "state.h"

struct student* newStudent(char* name) {
    struct student* s = (struct student*)malloc(sizeof(struct student));

    memset(s, 0, sizeof(s));
    s->name = name;
    s->status = WORKING;

    return s;
}

void execute(struct student* this, struct state* state) {
    // logic for a student
    printf("Would execute student %s.\n", this->name);
}

void* studentThread(void* arg) {
    struct student_thread_arg* data = (struct student_thread_arg*)arg;
    execute(data->student, data->state);

    free(data);
    return NULL;
}
