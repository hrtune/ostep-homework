#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Question: Explore the variants of exec() functions. */

int main(int argc, char *argv[]) {

    int rc;

    for(int i = 0; i < 5; i++) {

        rc = fork();

        if (rc < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) {
            // child
            switch(i) {

                case 0:
                    // execl (list): when knowing the number of arguments
                    printf("execl:\n");
                    execl("/bin/ls", "ls", "-l", "/usr", NULL);
                    break;

                case 1:
                    // execv (vector): pass arguments as an array
                    printf("execv:\n");
                    char *args[] = {"ls", "-l", "/usr", NULL};
                    execv("/bin/ls", args);
                    break;

                case 2:
                    // execlp and execvp (path): no need to specify the directory of the binary
                    printf("execlp:\n");
                    execlp("ls", "-l", "/usr", NULL);
                    break;
                
                case 3:
                    execvp("ls", args);
                    break;

               default:
                    // execve (vector + environment): specify env var for the command
                    printf("execve:\n");
                    char *args1[] = {"env", NULL};
                    char *env[] = {"MY_VAR=HELLO_WORLD!", NULL};
                    execve("/usr/bin/env", args1, env);
            }

        } else {
                // parent
                int rc_wait = wait(NULL);
                printf("\n");
        }

    }

    return 0;
}

/* Result: There are some variants of exec() for utility. Sometimes execlp() is easier to implement. execv() is
utilized to specify environment variables.
*/
