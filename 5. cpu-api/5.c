#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child
        sleep(1);
        printf("Child: Morning!\n");
   } else {
        // parent
        int rc_wait = wait(NULL);
        printf("Parent: Morning! How are you, No. %d?\n", rc_wait);
   }

    return 0;
}

/* Result: wait() takes int *status in which the exit status of the returned child will be stored.
    wait() returns the PID of the returned child if it exists. Otherwise, -1.
*/
