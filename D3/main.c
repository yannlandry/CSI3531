#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "state.h"
#include "student.h"
#include "ta.h"

// cleans the memory and exits
void clean_exit(int code, struct state* state, pthread_t* threads) {
    destroyState(state); // will call everything else

    if(threads != NULL) {
        free(threads);
    }

    exit(code);
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Please provide the name of at least one student.\n");
        fprintf(stderr, "Usage: tutoring <student>...\n");
        fprintf(stderr, "<student>: Name of a student, name as many as you want (max. 10).\n");

        clean_exit(EXIT_FAILURE, NULL, NULL);
    }

    int num_students = argc - 1;

    // state object
    struct state* state = newState();
    state->queue = newQueue();
    state->students = (struct student**)malloc((num_students) * sizeof(struct student*));
    state->num_students = num_students;
    state->ta = newTA();

    // populate students
    for(int i = 0; i < num_students; ++i) {
        state->students[i] = newStudent(argv[i + 1]);
    }

    // launch TA
    // he'll see empty queue and go to sleep
    // actually make thread here
    // in the mean time
    pthread_t ta_thread;
    int result = pthread_create(&ta_thread, NULL, taThread, (void*)state);
    if(result != 0) {
        fprintf(stderr, "Error creating a thread for the TA.\n");
        clean_exit(EXIT_FAILURE, state, NULL);
    }

    // launch students
    pthread_t* student_threads = (pthread_t*)malloc((num_students) * sizeof(pthread_t));

    for(int i = 0; i < num_students; ++i) {
        struct student_thread_arg* arg = (struct student_thread_arg*)malloc(sizeof(struct student_thread_arg));
        arg->student = state->students[i];
        arg->state = state;

        // here we actually start a thread
        // it will take care of deleting arg
        result = pthread_create(student_threads + i, NULL, studentThread, (void*)arg);
        if(result != 0) {
            fprintf(stderr, "Error creating a thread for student %s.\n", state->students[i]->name);
            clean_exit(EXIT_FAILURE, state, student_threads);
        }
    }

    // wait for the ta thread
    pthread_join(ta_thread, NULL);

    // wait for the student threads
    for(int i = 0; i < num_students; ++i) {
        pthread_join(student_threads[i], NULL);
    }

    clean_exit(EXIT_SUCCESS, state, student_threads);

    return 0;
}
