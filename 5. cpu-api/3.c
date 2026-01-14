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
        printf("hello\n");
    } else {
        // parent
        sleep(1); // wait for the child
        printf("goodbye\n");
    }

    return 0;
}

/* Result: To force the child to print first without wait(),
sleep() for a second can be used even though it is not logically assured.
*/
