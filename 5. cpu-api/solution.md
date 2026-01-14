# Solution for cpu-api

## fork.py

`fork.py` simulates the creation of processes.
- *a* has a single parent

The question is to speculate the state of the process tree.

Flags:
- c: show the answer
- F: simplified mode
- t: only shows tree
- s: seeds

## Questions

### 1.

```
./fork.py -s 10
```

Action: a forks b
- a
    - b

Action: a forks c
- a
    - b
    - c

Action: c EXITS
- a
    -b

Action: a forks d
- a
    - b
    - d

Action: a forks e
- a
    - b
    - d
    - e

### 2

With options:
```
-f <ratio_of_fork>
```

Larger the percentage is, higher the tree level is.

### 3. -t

With option:
```
./fork.py -t
```

After 5 actions (in my case):
- a
    - b
    - d
        - e

The actions are:
1. a fork b
2. a fork c
3. a fork d
4. c exits
5. d fork e

### 4. Exiting along with children

```
./fork.py -A a+b,b+c,c+d,c+e,c-
```

My expectation: After c exits, its children will be gone.

The result tree:
- a
  - b
  - d
  - e

Instead of killing `c`'s children, the shell decides to let `a` adopt them.

The `-R` flag reparents remaining children to local parent. With the flag, the result will be:
- a
  - b
    - d
    - e

The result is identical to my first speculation.

So, there are two modes when a process with children exits: repareinting to the top most parent or to the nearest parent.


### 5. -F

```
./fork.py -F
```

Actions:
1. Action: a forks b
2. Action: b forks c
3. Action: c forks d
4. Action: d EXITS
5. Action: b forks e

The final tree:
- a
  - b
    - c
    - e

### 6. -t and -F

```
./fork.py -t -F
```

After five actions:
    a
    ├── b
    ├── d
    └── e

Suppose there are five actions altogether, and processes are created in an alphabetical order.

At least b, d, and e are created by fork. c is missing, which means c exits at some point. One set of possible actions is:
1. a fork b
2. a fork c
3. c exits
4. a fork d
5. a fork e

Another set of possible actions are:
1. a fork b
2. a fork c
3. c fork d
4. c fork e
5. c exits

One of the deterministic situations is when there are 5 processes, where all actions are fork. 

