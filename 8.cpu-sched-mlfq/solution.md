# Homework: Simulation of Multi-Level Feedback Queue

## Notes

Concepts:
- **Quantum length** (time slice): maximum amount of time a process is allowed to run on the CPU before the scheduler interrupts it.
- **Allotment**: how many quantum unit a process can run at the priority level.

```
(Total time allowed at the Priority) = (Allotment at K) * (Quantum Length)
```

## 1.

Random two jobs with two queues, short length, and no I/O:
```
./mlfq.py -j 2 -n 2 -m <max len> -M 0
```

#### The first attempt 


```
./mlfq.py -j 2 -n 2 -m 10 -M 0 -s 11
```
Queues:
- Queue 1:
  - quantum length: 10
  - allotment: 1
- Queue 0:
  - quantum length: 10
  - allotment: 1

Jobs:
- Job  0: startTime   0 - runTime   5 - ioFreq   0
- Job  1: startTime   0 - runTime   9 - ioFreq   0

Trace:

| Time | Job | Priority | Allotment | Result |
| --- | --- | --- | --- | --- |
| 0-4 | 0 | 1 | 1 | done |
| 5-13 | 1 | 1 | 1 | done |


#### The second attempt

```
./mlfq.py -j 2 -n 2 -m 20 -M 0 -s 12
```

Queues:
- Queue 1:
  - quantum length: 10
  - allotment: 1
- Queue 0:
  - quantum length: 10
  - allotment: 1

Job List:
- Job  0: startTime   0 - runTime  10 - ioFreq   0
- Job  1: startTime   0 - runTime  13 - ioFreq   0

Trace:

| Time | Job | Priority | Allotment | Result |
| --- | --- | --- | --- | --- |
| 0-9 | 0 | 1 | 1 | done |
| 10-19 | 1 | 1 | 1 | domote |
| 20-22 | 1 | 0 | 1 | done | 


## 2. Reproducing Examples

#### Figure 8.2

Figure 8.2 (long-running job):
- Queues: 3
- Quantum length: 10
- Boost freq: 0
- Allotment: 1
- Job0:
  - Start time: 0
  - Run time: 200

The command:
```
./mlfq.py -n 3 -q 10 -a 1 -B 0 -l 0,200,0
```

#### Figure 8.3 Left

Figure 8.3 Left (two jobs):
- Queues: 3
- Quantum length: 10
- Allotment: 1
- Boost freq: 0
- Job0:
  - Start time: 0
  - Run time: 200
- Job1:
  - Start time: 100
  - Run time: 20

```
./mlfq.py -n 3 -q 10 -a 1 -B 0 -l 0,200,0:100,20,0
```

#### Figure 8.3 Right

Figure 8.3 Left (two jobs):
- Queues: 3
- Quantum length: 10
- Allotment: 1
- I/O time: 4
- Boost freq: 0
- Stay at I/O
- Job0:
  - Start time: 0
  - Run time: 180
- Job1:
  - Start time: 50
  - Run time: 20
  - I/O Freq: 1

```
./mlfq.py -n 3 -q 10 -a 1 -B 0 -i 4 -S -l 0,180,0:50,20,1 
```

#### Figure 8.4 Left (Without Priority Boost)

Figure 8.4 Left:
- Queues: 3
- Quantum length: 10
- Allotment: 1
- I/O time: 1
- Boost freq: 0
- Stay at I/O
- Job0:
  - Start time: 0
  - Run time: 200
- Job1:
  - Start time: 100
  - Run time: 50
  - I/O Freq: 1
- Job2:
  - Start time: 100
  - Run time: 50
  - I/O Freq: 1


```
./mlfq.py -n 3 -q 10 -a 1 -B 0 -i 1 -S -l 0,200,0:100,50,1:100,50,1
```

#### Figure 8.4 Right (Without Priority Boost)

Figure 8.4 Right:
- Queues: 3
- Quantum length: 10
- Allotment: 1
- I/O time: 1
- Boost freq: 30
- Stay at I/O
- Job0:
  - Start time: 0
  - Run time: 200
- Job1:
  - Start time: 100
  - Run time: 50
  - I/O Freq: 1
- Job2:
  - Start time: 100
  - Run time: 50
  - I/O Freq: 1


```
./mlfq.py -n 3 -q 10 -a 1 -B 30 -i 1 -S -l 0,200,0:100,50,1:100,50,1
```

#### Figure 8.5 Left (Without Gaming Tolerance)

Figure 8.4 Left:
- Queues: 3
- Quantum length: 10
- Allotment: 1
- I/O time: 1
- Boost freq: 0
- Stay at I/O
- Job0:
  - Start time: 0
  - Run time: 200
- Job1:
  - Start time: 100
  - Run time: 100
  - I/O Freq: 5

```
./mlfq.py -n 3 -q 10 -a 1 -B 0 -i 1 -S -l 0,200,0:100,100,5
```

#### Figure 8.5 Right (With Gaming Tolerance)

Figure 8.5 Right:
- Queues: 3
- Quantum length: 10
- Allotment: 1
- I/O time: 1
- Boost freq: 0
- Stay at I/O
- Job0:
  - Start time: 0
  - Run time: 200
- Job1:
  - Start time: 100
  - Run time: 100
  - I/O Freq: 5

```
./mlfq.py -n 3 -q 10 -a 1 -B 0 -i 1 -l 0,200,0:100,100,5
```

#### Figure 8.6 (Lower Priority, Longer Quanta)

Figure 8.6:
- Queues: 3
- Quantum length:
  - Q2: 10
  - Q1: 20
  - Q0: 40
- Allotment: 2
- Boost freq: 0
- Job0:
  - Start time: 0
  - Run time: 140
- Job1:
  - Start time: 0
  - Run time: 140

```
./mlfq.py -n 3 -Q 10,20,40 -a 2 -B 0 -l 0,140,0:0,140,0
```

## 3. Just Round Robin

MLFQ has multiple queues while a just round-robin scheduler does not. So, the setting:
- Queues: 1
- Quantum length (time slice): 10 (for example)
- Jobs: 3 (for example)

```
./mlfq.py -n 1 -q 10 -j 3
```

## 4. Gaming Scheduler

The setting:
- Queues: 2
- Allotment: 10
- Quantum length: 10
- IO time: 1
- Stay at IO
- Job0 (victim):
  - Start time: 0
  - Run time: 200
- Job1 (gamer):
  - Start time: 50
  - Run time 200
  - IO Freq: 100

```
./mlfq.py -n 2 -q 10 -a 10 -i 1 -S -l 0,200,0:50,200,100
```

In the time segment from 140 to 290, Job0 could only run 1 time on the CPU. (Job1's usage: 149/150 ~ 0.99)

## 5. 

When the boost occurs once per $T$ time, then
$$
10 / T = 0.05
$$
must hold to obtain 5% of the CPU time at least. Such $T$ is:
$$
T = 10 / 0.05 = 200
$$

So, the priority boost must occur once per 200 ms to guarantee 5%. 

## 6.