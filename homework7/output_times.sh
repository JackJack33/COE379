#!/bin/bash

output_file="times.txt"
threads_list=(8 16 32)

> "$output_file"
> "$output_file2"
echo "threads vectorsize sequential_time parallel_time" > "$output_file"

for threads in "${threads_list[@]}"; do
    for (( vectorsize = 1; vectorsize <= 10000; vectorsize+=25 )); do

	output=$(OMP_NUM_THREADS=$threads ./vectorsum $vectorsize)
	sequential_time=$(echo "$output" | grep "Sequential" | awk '{print $3}')
	parallel_time=$(echo "$output" | grep "Threads" | awk '{print $4}')
	
	echo "$threads $vectorsize $sequential_time $parallel_time" >> "$output_file"
	
    done
done

for (( vectorsize = 1; vectorsize <= 10000; vectorsize+=25 )); do

    output=$(OMP_NUM_THREADS=13 ./affinity_vectorsum $vectorsize)
    sequential_time=$(echo "$output" | grep "Sequential" | awk '{print $3}')
    parallel_time=$(echo "$output" | grep "Threads" | awk '{print $4}')
    
    echo "13 $vectorsize $sequential_time $parallel_time" >> "$output_file"

done
