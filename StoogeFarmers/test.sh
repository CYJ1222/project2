#!/bin/bash
#use way:
#chmod +x test.sh
#./test.sh
#
# Number of runs
NUM_RUNS=50

# Output file
OUTPUT_FILE="runtimes.txt"


# Clear output file
> $OUTPUT_FILE

# Run Copy and ForkCopy multiple times for each buffer size
    for ((i=1; i<=$NUM_RUNS; i++)); do
        echo "Run $i"
        ./lcm >> $OUTPUT_FILE
    done

