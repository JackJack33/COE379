#!/bin/bash

output_file="times.txt"

> "$output_file"
echo "ksp_type pc_type sub_pc_type PCSetUp Flops_per_sec Iterations MatMult" > "$output_file"

for ksp_type in cg bcgs gmres; do
    for pc_type in bjacobi asm; do
        for sub_pc_type in lu ilu; do
            output=$(./ksp -n 100 -ksp_type $ksp_type -pc_type $pc_type -sub_pc_type $sub_pc_type -log_summary)
            pc_setup=$(echo "$output" | grep "PCSetUp" | awk 'NR==1 {print $4}')
            flops_per_sec=$(echo "$output" | grep "Flops/sec:" | awk 'NR==1 {print $4}')
            iterations=$(echo "$output" | grep "iterations" | awk 'NR==1 {print $6}')
            mat_mult=$(echo "$output" | grep "MatMult" | awk 'NR==1 {print $2}')
            echo "$ksp_type $pc_type $sub_pc_type $pc_setup $flops_per_sec $iterations $mat_mult" >> "$output_file"
        done
    done
done





