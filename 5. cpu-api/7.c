#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Question: what if print after closed stdout? */

int main(int argc, char *argv[]) {

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child
        close(STDOUT_FILENO);
        printf("Hello!\n");
   } else {
        // parent
   }

    return 0;
}

/* Result: My expectation was the process writes to the stdout after it is closed because
I thought it finds the earliest open file descriptor, which is 1. However, it was wrong.
printf() calls write(), and it returns -1, which means error (errno=EBADF: bad file descriptor).
*/

