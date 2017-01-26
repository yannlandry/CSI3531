#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // do some validation
    if(argc != 2) {
        fprintf(stderr, "Usage: cpr <num>\n<num>: Number of processes to create.\n");
        return 1;
    }

    int num = atoi(argv[1]);
    if(num < 1) {
        fprintf(stderr, "Error: Please enter an integer equal or greater to 1 as argument.\n");
        return 1;
    }

    // show up
    char procbuf[128];
    sprintf(procbuf, "I am process #%d.\n", num);
    write(1, procbuf, strlen(procbuf));

    // recurse
    if(num > 1) {
        int fd[2];
        pipe(fd); // make a nice shiny pipe

        int pid = fork();

        // error
        if(pid == -1) {
            fprintf(stderr, "Forking process failed.\n");
        }

        // child
        else if(pid == 0) {
            dup2(fd[1], 1); // stdout now writes to pipe

            // prep argument
            char numstr[10];
            sprintf(numstr, "%d", num - 1);

            // and spawn!
            execlp(argv[0], argv[0], numstr, NULL);
        }

        // parent
        else {
            close(fd[1]); // close our own end

            char buffer[128];
            int nbytes = 0;

            while( (nbytes = read(fd[0], buffer, 128)) > 0 ) {
                write(1, buffer, nbytes);
            }

            wait(NULL);
        }
    }

    close(1);

    return 0;
}
