#include <unistd.h>
#include <stdio.h>
#include <mach/mach_time.h>

int main() {

    int iterations = 1000000;
    mach_timebase_info_data_t info;
    mach_timebase_info(&info);

    uint64_t start = mach_absolute_time();
    for (int i=0; i < iterations; i++) {
        getpid(); // a system call
    }
    uint64_t end = mach_absolute_time();

    uint64_t total_ns = (end - start) * info.numer / info.denom;

    printf("A system call's cost in nanoseconds ~ %llu[ns]\n", total_ns / iterations);

    return 0;
}



