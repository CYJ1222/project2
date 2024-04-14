#!/bin/bash
#use way:
#chmod +x test.sh
#./test.sh
#
# Number of runs
NUM_RUNS=1
#
# Output file
OUTPUT_FILE="test.md"


# Clear output file
> $OUTPUT_FILE

# Run Copy and ForkCopy multiple times for each buffer size
    for ((i=1; i<=$NUM_RUNS; i++)); do
        echo "Run $i"
        ./StoogeFarmers/lcm >> $OUTPUT_FILE
        ./Party/party>> $OUTPUT_FILE
    done
