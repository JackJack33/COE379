import matplotlib.pyplot as plt
import numpy as np

vectorsizes = []
sequential_times = []
parallel_times = []
difference_times = []

with open('times.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        vectorsizes.append(int(data[0]))
        sequential_times.append(100000 * float(data[1]))
        parallel_times.append(100000 * float(data[2]))
        difference_times.append(100000 * (float(data[1]) - float(data[2])))

fig, axs = plt.subplots(2, 1)

# first plot

axs[0].scatter(vectorsizes, sequential_times, label='Sequential', color='blue', marker='o', alpha=0.5)
axs[0].scatter(vectorsizes, parallel_times, label='Parallel', color='red', marker='o', alpha=0.5)

axs[0].set_ylabel('Time (μs)')
axs[0].grid(True)
axs[0].legend(loc='upper left')

axs[0].set_title('Vector Size vs. Time for Sequential and Single-Threaded Parallel Execution')

# second plot

axs[1].scatter(vectorsizes, difference_times, label='Signed Difference', color='gray', marker='o', alpha=0.5)

axs[1].set_ylabel('Time (μs)')
axs[1].grid(True)
axs[1].legend(loc='upper left')
axs[1].set_xlabel('Vector Size')

plt.show()
