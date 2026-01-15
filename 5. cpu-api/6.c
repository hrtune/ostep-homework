#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    // someone's child
    int other = fork();
    if (other == 0) {
        printf("Someone's child (%d): Hi!\n", getpid());
        exit(0);   
    }

    // child
    int child = fork();
    if (child == 0) {
        sleep(1);
        printf("Child (%d): Dad!\n", getpid());
        exit(0);
    }

    // parent

    int hello_other = waitpid(other, NULL, 0);
    printf("Parent: Hi, %d!\n", hello_other);

    int wait_child = waitpid(child, NULL, 0);
    printf("Parent: %d! How was your day?\n", wait_child);

    return 0;
}

/* Result: waitpid() can wait for a specific PID and it is useful when the parent has multiple children.
    It also takes int options, where "WNOHANG" means it does not wait for the child.
*/
