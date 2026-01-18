# Homework: Measurement of System Call

## Objective
Measure the cost of a system call and context switch in a computer.

## Environment

MacBook Air (M4)
- ~4.5GHz
- MacOS

## Tools

Since I'm running on Apple Silicon, `mach_absolute_time()` has better accuracy than `gettimeofday()`.

Usage of `mach_absolute_time()`:
```c
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

}
```

## Measuring strategies

### Measuring the cost of a system call

`getpid()` performs a system call with very little work. So, measuring it approximates the cost of a system call.


### Measuring the cost of a context switch

Reading an empty pipe yields the CPU. So, read and write pipes between two processes creates sequential context switches.

The logic:
```c
// --- in process A ---
for (int i = 0; i < iterations; i++) {
            read(pipe1[0], &buf, 1);
            write(pipe2[1], "x", 1);
}
// ...
// --- in process B ---
uint64_t start = mach_absolute_time();
for (int i = 0; i < iterations; i++) {
    write(pipe1[1], "x", 1);
    read(pipe2[0], &buf, 1);
}
uint64_t end = mach_absolute_time();
// ...
```

- Reading a filled pipe depletes the pipe.
- Reading the pipe again, which is now empty, causes a context switch to the other.
- Fill the other pipe that is read by the other process. 
  - triggers the other process who wants to read it.
  - avoids the deadlock.
- Repeats the "ping-pong."

## Result (on my MacBook Air M4)

The cost of a system call ~ 2 nanoseconds.
The cost of a context switch ~ 2.2 microseconds.

The cost of a context switch is much larger than that of a system call because the former needs saving and restoring the context, which includes control registers, the Translation Lookaside Buffer, etc. It also causes the "cold cache problem," where the process experience cache misses.