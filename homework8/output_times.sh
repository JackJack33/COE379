#!/bin/bash

output_file="times.txt"

> "$output_file"
echo "threads size iterations precision time" > "$output_file"

for (( threads = 1; threads <= 16; threads++ )); do
    for (( size = 2; size <= 100000; size*=2 )); do

	output=$(OMP_PROC_BIND=True OMP_NUM_THREADS=$threads ./jacobi $size)
	iterations=$(echo "$output" | grep "Converged" | awk '{print $3}')
	precision=$(echo "$output" | grep "Converged" | awk '{print $6}')
	time=$(echo "$output" | grep "Converged" | awk '{print $10}')
	
	echo "$threads $size $iterations $precision $time" >> "$output_file"
	
    done
done
