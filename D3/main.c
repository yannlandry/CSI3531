/* THE PLAN:
    files: main.c student.c ta.c queue.c
    for each file, one struct + methods to implement it
    make the queue thread-safe
    ta takes care of picking the queue? no, because the student awakes the ta
        so the student must check if it's first in line and if so lock the ta for a while
    add a method for student programming
    and a method for a student seeking help?

    OH FUCK: ta needs its own thread with a semaphone and shit
*/

#include <pthread.h>
#include <stdio.h>

#include "queue.h"
#include "state.h"
#include "student.h"
#include "ta.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Please provide the name of at least one student.\n");
        fprintf(stderr, "Usage: tutoring <student>...\n");
        fprintf(stderr, "<student>: Name of a student, name as many as you want (max. 10).\n");
        return 1;
    }

    num_students = argc - 1;

    // state object
    struct state* state = newState();
    state->queue = newQueue();
    state->students = (struct student**)malloc((num_students) * sizeof(struct student*))
    state->ta = newTA();

    // populate students
    for(int i = 0; i < num_students; ++i) {
        state->students[i] = newStudent(argv[i + 1]);
    }

    // launch TA
    // he'll see empty queue and go to sleep
    // actually make thread here
    // in the mean time
    taThread(state);

    // launch students
    thread_t* threads = (thread_t*)malloc((num_students) * sizeof(thread_t))

    for(int i = 0; i < num_students; ++i) {
        struct student_thread_arg* arg = (struct student_thread_arg*)malloc(sizeof(student_thread_arg));
        arg->student = state->students[i];
        arg->state = state;

        // here we actually start a thread

        // will take care of deleting the arg
        studentThread(arg);
    }

    // here join the ta thread

    // then join the student threads

    // then purge the TA, the students, and the entire world
}
