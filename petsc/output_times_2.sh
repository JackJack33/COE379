#!/bin/bash

output_file="times.txt"

> "$output_file"
echo "unsymmetry iterations" > "$output_file"

unsymmetry=-1.0
while (( $(bc <<< "$unsymmetry <= 1.0") )); do

    output=$(./ksp -n 100 -ksp_type gmres -unsymmetry $unsymmetry)
    iterations=$(echo "$output" | grep "iterations" | awk '{print $6}')

    echo "$unsymmetry $iterations" >> "$output_file"

    unsymmetry=$(bc <<< "$unsymmetry + 0.2")

done
