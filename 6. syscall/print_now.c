#include <stdio.h>
#include <stdint.h>
#include <mach/mach_time.h>

int main() {

    // Get time base info (will be conversion factor)
    mach_timebase_info_data_t info;
    mach_timebase_info(&info);

    // Capture the time now
    uint64_t now_tick = mach_absolute_time();

    // Convert [ticks] -> [nanoseconds]
    uint64_t now_ns = now_tick * info.numer / info.denom; 

    // Print it
    printf("Accurate time: %llu[ns]\n", now_ns);

    return 0;

}