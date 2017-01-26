#ifndef STUDENT_H
#define STUDENT_H

#include "state.h"

struct student {
    char* name;
    enum{WORKING, WAITING, CONSULTING} status;
};

struct student_thread_arg {
    struct student* student;
    struct state* state;
}

struct student* newStudent(char* name);

void* studentThread(void* arg);

#endif
