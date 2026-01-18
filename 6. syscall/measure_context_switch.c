#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach/mach_time.h>

int main() {

    int pipe1[2], pipe2[2];  // pipe[0]: read end, pipe[1]: write end
    pipe(pipe1); pipe(pipe2);
    int iterations = 10000;

    if (fork() == 0) { // Child Process
        char buf;
        for (int i = 0; i < iterations; i++) {
            read(pipe1[0], &buf, 1);
            write(pipe2[1], "x", 1);
        }
        exit(0);
    } else { // Parent Process
        char buf;
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);

        uint64_t start = mach_absolute_time();
        for (int i = 0; i < iterations; i++) {
            write(pipe1[1], "x", 1);
            read(pipe2[0], &buf, 1);
        }
        uint64_t end = mach_absolute_time();

        uint64_t total_ns = (end - start) * info.numer / info.denom;

        // Divide by (iterations * 2) because each loop has 2 context switches
        printf("The cost of a context switch ~ %llu [ns]\n", total_ns / (iterations * 2));
    }

    return 0;
}