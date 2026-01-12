# Solution

## Usage of process-run.py

Define a list of processes (`-l`)
```
python process-run.py -l n1:p1,n2:p2,...
```
- n: number of instructions in the process
- p: probability(0-100) if the process uses the cpu, otherwise it uses IO

Show the result (`-c`)
```
prompt> ./process-run.py -l 5:100,5:100 -c
```
- The column CPU or IO says 1 if the process uses one at the moment.

A process with only IO operations that takes 5 for each
```
python process-run.py -l 3:0 -L 5
```
- Each IO operation takes 1 tick for making an IO request and 1 tick for the completion.

## Questions

### 1.

Run:
```
process-run.py -l 5:100,5:100
```

In this case, there is no blocking event, which is solely an IO event. So, the CPU usage must be 100% overall.

### 2.

Run:
```
process-run.py -l 4:100,1:0
```

There are two processes:
    - p0: 4 instructions for CPU
    - p1: 1 operation for IO

Since the first process `p0` has the highest priority, the second process `p1` must wait until it finishes.

The flow is:
1. p1 - job (4 ticks)
2. p2 - io start (1 tick)
3. Blocked by p2 (5 ticks)
4. p2 - io complete (1 tick)

The CPU's total busy time is calculated by:
$$
T = B / (B + I) \tag{2.1}
$$
where,
- $T$: total time
- $B$: busy time
- $I$: idle time

Since $B = 6$ and $I = 5$,
$$
T = 6 / (6 + 5) \approx 0.55
$$

### 3.

Run:
```
process-run.py -l 1:0,4:100
```

This time, the first process does 1 routine of I/O, which has the priority. So, the CPU usage:
1. p0 - io start (1 tick)
2. p1 - job (4 ticks)
3. Blocked by p0 (1 tick)
4. p0 - io stop (1 tick)

So, the total usage time of the CPU:
$$
T = 6 / 7 \approx 0.86
$$

The the order of process affects the total busy time of the CPU because a normal job can be run while the IO operation occurs in this order, compared to the opposite order.


### 4. SWITCH_ON_END

Run:
```
process-run.py -l 1:0,4:100 -S SWITCH_ON_END
```

My expectation is that it creates the same CPU usage as the Question 2 because it does not allow the CPU to switch between the processes.

The flow:
1. p0 - io start (1 tick)
2. Blocked by p0 (5 tick)
3. p0 - io end (1 tick)
4. p1 - job (4 tick)

The total CPU usage time:
$$
T = 6 / 11 \approx 0.55
$$


### 5. SWITCH_ON_IO

```
process-run.py -l 1:0,4:100 -c -S SWITCH_ON_IO
```

My expectation is that it produces the same trace as the Question 3. And, it does.

### 6. IO_RUN_LATER

Run:
```
./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
```

IO_RUN_LATER let IO processes have less priority than normal processes when their IO operations are done. It leads to the less efficient usage of the CPU because an IO request must be issued before the other process's normal jobs are initiated.

With the `-I IO_RUN_LATER` flag, the CPU usage is 67.74%, which is not optimal.


### 7. IO_RUN_IMMEDIATE

Run:
```
./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
```

With the option `-I IO_RUN_IMMEDIATE`, the CPU usage is improved to the most optimal 100% because all the normal jobs are done while the other's IO operation is on going.

### 8. Randoom

With options:
```
-s 1 -l 3:50,3:50
```

Process 0: cpu - io - io
Process 1: cpu - cpu - cpu

The expected trace would be:
1. p0 - cpu (1 tick)
2. p0 - io start (1 tick)
3. p1 - cpu (3 ticks)
4. p0 - block (2 ticks)
5. p0 - io done (1 tick)
6. p0 - io start (1 tick)
7. p0 - block (5 ticks)
8. p0 - io done (1 tick)

So, the overall CPU usage is `8 / (8 + 7) ~ 0.53`, which is not favorable but it seems it cannot be improved from that trace. Every p1's cpu instructions are done while the other's IO operations.

With options 
```
-s 2 -l 3:50,3:50
```

Process 0: io - io - cpu
Process 1: cpu - io - io

The trace with no IO policies:
1. p0 - io start (1)
2. p1 - cpu (1)
3. p1 - io start (1)
4. blocked (3)
5. p0 - io done (1)
6. p0 - io start (1)
7. p1 - io done (1)
8. p1 - io start(1)
9. blocked (3)
10. p0 - io done (1)
11. p0 - cpu (1)
12. p1 - io done (1)

The total usage: `10 / (10 + 6) ~ 0.63`. Every CPU instruction in both processes was not blocked by the other process's IO operations. So, it seems optimal. 

With options:
```
-s 3 -l 3:50,3:50
```

Process 0: cpu - io - cpu
Process 1: io - io - cpu

The trace:
1. p0 - cpu (1)
2. p0 - io start (1)
3. p1 - io start (1)
4. blocked (4)
5. p0 - io end (1)
6. p0 - cpu (1)
7. p1 - io end (1)
8. p1 - io start (1)
9. blocked (5)
12. p1 - io end (1)
13. p1 - cpu (1)

This time, `-I IO_RUN_IMMEDIATE` improves the CPU usage slightly because the last cpu routine of p0 now runs while p1's IO operation.

## Summary

To maximize CPU usage, the OS should let the CPU run awaiting IO requests or completion since an IO operation can be done concurrently but is slow.