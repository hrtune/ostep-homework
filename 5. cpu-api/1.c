#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int x = 100;

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child
        printf("child: x = %d\n", x);
        x = x + 1;
        printf("child: x = %d\n", x);
    } else {
        // parent
        printf("parent: x = %d\n", x);
        x = x + 10;
        printf("parent: x = %d\n", x);
    }

    return 0;
}

/* Result:
    Memory space including x is copied to both process,
    creating separate name space for both the child and parent.
    So, the variable x is updated independently, having their own values.
*/
