#!/bin/bash

output_file="times.txt"

> "$output_file"
echo "vectorsize sequential_time parallel_time" > "$output_file"

for (( vectorsize = 1; vectorsize <= 50000; vectorsize+=100 )); do
    
    output=$(OMP_NUM_THREADS=1 ./vectorsum $vectorsize)
    sequential_time=$(echo "$output" | grep "Sequential" | awk '{print $3}')
    parallel_time=$(echo "$output" | grep "Threads" | awk '{print $4}')
    
    echo "$vectorsize $sequential_time $parallel_time" >> "$output_file"
    
done
