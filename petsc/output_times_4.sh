#!/bin/bash

output_file="output_data.txt"

> "$output_file"
echo "ksp_type pc_type sub_pc_type PCSetUp Flops_per_sec" > "$output_file"

for ksp_type in cg bcgs gmres; do
    for pc_type in bjacobi asm; do
        for sub_pc_type in lu ilu; do
            output=$(./ksp -n 100 -ksp_type $ksp_type -pc_type $pc_type -sub_pc_type $sub_pc_type -log_summary)
            pc_setup=$(echo "$output" | grep "PCSetUp" | awk '{print $4}')
            flops_per_sec=$(echo "$output" | grep "Flops/sec:" | awk '{print $4}')
            echo "$ksp_type $pc_type $sub_pc_type $pc_setup $flops_per_sec" >> "$output_file"
        done
    done
done








