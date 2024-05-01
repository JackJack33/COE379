#!/bin/bash

output_file="times.txt"

> "$output_file"
echo "threads time" > "$output_file"

for (( threads = 1; threads <= 32; threads+=1 )); do
    
    output=$(OMP_NUM_THREADS=$threads ./raymarch)
    time=$(echo "$output" | grep "Marched" | awk '{print $4}')
    
    echo "$threads $time" >> "$output_file"
    
done
