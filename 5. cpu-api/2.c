#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/* Question: Can the parent and child processes open and write
the same file at the same time?
*/

int main(int argc, char *argv[]) {

    int x = 100;

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child
        int fd = open("./file2", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        // sleep(1); // comment out when parent writes first
        const char *child_text = "I am Child\n";
        write(fd, child_text, strlen(child_text));
        printf("child wrote the file\n");
        sleep(1); // Sleep for 1 second
        close(fd);
    } else {
        // parent
        int fd = open("./file2", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        // sleep(1); // comment out when child writes first
        const char *parent_text = "I am Parent\n";
        write(fd, parent_text, strlen(parent_text));
        printf("parent wrote the file\n");
        int rc_wait = wait(NULL);
        close(fd); 

        // Print the file
        char *myargs[3];
        myargs[0] = strdup("cat");
        myargs[1] = strdup("./file2");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);

    }

    return 0;
}

/* Result: This code does not procude any error in both macOS and Kali Linux. The reasons are:
    - fork() separate them, creating independent memory and file descriptor tables.
    - The operating systems selialize the hardware access to the disk, avoiding the race condition. 
*/
