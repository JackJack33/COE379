#!/bin/bash

output_file="times.txt"

> "$output_file"
echo "vectorsize iterations" > "$output_file"

for (( vectorsize = 100; vectorsize <= 1000; vectorsize+=100 )); do
    
    output=$(./ksp -n $vectorsize -ksp_type gmres)
    iterations=$(echo "$output" | grep "iterations" | awk '{print $6}')
    
    echo "$vectorsize $iterations" >> "$output_file"
    
done
