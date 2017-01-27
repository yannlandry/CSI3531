#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "state.h"
#include "student.h"
#include "ta.h"

int main(int argc, char* argv[]) {
    // TODO add signal handler for Ctrl+C
    // http://stackoverflow.com/questions/4217037/catch-ctrl-c-in-c

    if(argc < 2) {
        fprintf(stderr, "Please provide the name of at least one student.\n");
        fprintf(stderr, "Usage: tutoring <student>...\n");
        fprintf(stderr, "<student>: Name of a student, name as many as you want (max. 10).\n");
        return 1;
    }

    int num_students = argc - 1;

    // state object
    struct state* state = newState();
    state->queue = newQueue();
    state->students = (struct student**)malloc((num_students) * sizeof(struct student*));
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
        exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);
        }
    }

    // wait for the ta thread
    pthread_join(ta_thread, NULL);

    // wait for the student threads
    for(int i = 0; i < num_students; ++i) {
        pthread_join(student_threads[i], NULL);
    }

    // then purge the TA, the students, and the entire world
    sem_destroy(&state->ta->semaphore);
    free(state->ta);
    free(state->queue);
    for(int i = 0; i < num_students; ++i) {
        free(state->students[i]);
    }
    free(state);
    free(student_threads);

    return 0;
}

// function for signal handler
// global var to continue
// global var to hold interrupt data
// function to set interrupt data
