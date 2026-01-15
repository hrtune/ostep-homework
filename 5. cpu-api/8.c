#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Question: use pipe to communicate between processes */

/* Usage of pipe(): int pipe(int pipefd[2])
    returns 0 if success, -1 if error.
    It stores fd of the read end to pipefd[0]
        and fd of the write end to pipefd[1].
*/

int main(int argc, char *argv[]) {

    printf("Parent: What is the answer of 42 / 6 ?\n");

    int fd[2];

    if (pipe(fd) == -1) {
        // error
        fprintf(stderr, "pipe failed\n");
        return 1;
    }

    int childA = fork();
    if (childA < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (childA == 0) {
        close(fd[0]);
        char *ans = "It's 5!";
        write(fd[1], ans, strlen(ans) + 1);
        close(fd[1]);
        exit(0);
    }

    int childB = fork();
    if (childB < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (childB == 0) {
        sleep(1);
        close(fd[1]);
        char buffer[10];
        read(fd[0], buffer, sizeof(buffer));
        printf("ChildB: %s\n", buffer);
        close(fd[0]);
        exit(0);
    }

    // parent
    waitpid(childB, NULL, 0);
    printf("You're wrong!\n");
    

    return 0;
}

/* Result:
*/
