#!/bin/bash

# Configuration
TOTAL_RUNS=20  # Total number of times to run the command
INCREMENT=5     # How much to increase the numbers by

# Initial base values
BASE_A=1
BASE_B=5
BASE_C=10

for (( i=0; i<$TOTAL_RUNS; i++ )); do
    # Calculate the current offset
    # The offset now increases with each iteration
    OFFSET=$(( i * INCREMENT ))

    # Calculate the new values for the -l option
    VAL1=$(( BASE_A + OFFSET ))
    VAL2=$(( BASE_B + OFFSET ))
    VAL3=$(( BASE_C + OFFSET ))

    # Format the comma-separated string
    L_OPTION="${VAL1},${VAL2},${VAL3}"

    echo "Iteration $((i+1)): Executing with -l $L_OPTION"
    
    # Execute the command
    python3 ./scheduler.py -l "$L_OPTION" -p SJF -c
done