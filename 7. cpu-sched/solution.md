# Homework: Simulate Scheduler

## Usage of scheduler.py

```
./scheduler.py -p [policy] -j [num of jobs] -s [seed]
```
- `-c`: shows the answer
- `-l j1,j2,j3,...`: specify run time of each job in an integer.

## Questions

### 1.

Response and turnaround time of SJF with 200 run time for each:
| Job | Response Time | Turnaround Time |
| --- | --- | --- |
| A | 0 | 200 |
| B | 200 | 400 |
| C | 400 | 600 |

Average response time of SJF:
$$
(0 + 200 + 400) / 3 = 200
$$

Average turnaround time of SJF:
$$
(200 + 400 + 600) / 3 = 400
$$

SJF and FIFO creates the same average response and turnaround time in this case. So, the averages are:

|  | Average Response | Average Turnaround |
| --- | --- | --- |
| SJF | 200 | 400 |
| FIFO | 200 | 400 |

### 2.

Response and turnaround time of SJF for each job:

| Job | Run Time | Response Time | Turnaround Time |
| --- | --- | --- | --- |
| A | 100 | 0 | 100 |
| B | 200 | 100 | 300 |
| C | 300 | 300 | 600 |

The average response time of SJF:
$$
(0 + 100 + 300) / 3 \approx 133
$$

The average turnaround time of SJF:
$$
(100 + 300 + 600) / 3 \approx 333
$$

SJF and FIFO creates the same average response and turnaround time in this case because the jobs are in ascending order and are scheduled in the same order. So, the averages are:

|  | Average Response | Average Turnaround |
| --- | --- | --- |
| SJF | 133 | 333 |
| FIFO | 133 | 333 |

### 3.

The round robin policy runs the jobs, A, B, and C in the order:
```
A, B, C, A, B, C, ...
```

If the sequence of `A,B,C` is done 100 times, then the total run time is $3 \cdot 100 = 300$. But the last two `B, C` is redundant. So, the turnaround time of A is:
$$
3 \cdot 100 - 2 = 298
$$

After A has been finished, the sequence of jobs will be `B, C, B, C, ...`. In the 300 time, B is done 100 time. The remaining 100 time for B is done after $2 \cdot 100 - 1 = 199$. So the turnaround time of B is:
$$
300 + (2 \cdot 100 - 1) = 499
$$

The job C has been done after the all job slices are finished. So, the turnaround time of C:
$$
100 + 200 + 300 = 600
$$

The response and turnaround time of RR for each job:

| Job | Run Time | Response Time | Turnaround Time |
| --- | --- | --- | --- |
| A | 100 | 0 | 298 |
| B | 200 | 1 | 499 |
| C | 300 | 2 | 600 |

The average response:
$$
(0 + 1 + 2) / 3 = 1
$$

The average turnaround:
$$
(298 + 499 + 600) / 3 \approx 466
$$

The average time of RR, SJF, and FIFO:

|  | Average Response | Average Turnaround |
| --- | --- | --- |
| SJF | 133 | 333 |
| FIFO | 133 | 333 |
| RR | 1 | 466 |

### 4.

FIFO and SJF has the same turnaround time if the jobs are sorted in asceinding order in terms of the run time. It is because the schedules of both are identical in that case.

### 5.

If the quantum length of RR is equal to or larger than the run time of the longest job, then SJF and RR will have the same response speed.

### 6.

The response time $T$ of $n^{th}$ job, $T_n$ in SJF is:
$$
T_{n} = \sum\limits_{i=0}^{n-1}{w_i}
$$

So, if the workloads of the jobs increase, then the response time tends to increase.

`simulate_sjf_response.sh` does the simulation when the workloads increase.

### 7.

The average response time $T_{avg}$ with $N$ jobs when the policy is RR and its quantum length is $q$:
$$
T_{avg} = \frac{0 + q + 2q + \ldots + q(N-1)}{N} = q\frac{0 + 1 + 2 + \ldots + (N-1)}{N} 
$$
$$
= q\frac{N(N-1)}{2N} = q\frac{N-1}{2}
$$

As the quantum length increases, the average response time also increases.

