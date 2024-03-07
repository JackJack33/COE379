import matplotlib.pyplot as plt
import numpy as np

threads = []
vectorsizes = []
sequential_times = []
parallel_times = []

with open('times.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        threads.append(int(data[0]))
        vectorsizes.append(int(data[1]))
        sequential_times.append(100000 * float(data[2]))
        parallel_times.append(100000 * float(data[3]))

unique_threads = sorted(set(threads))

fig, axs = plt.subplots(len(unique_threads), 1)

for i, thread_size in enumerate(unique_threads):

    thread_indices = [i for i, thread in enumerate(threads) if thread == thread_size]
    current_vectorsizes = [vectorsizes[i] for i in thread_indices]
    current_sequential_times = [sequential_times[i] for i in thread_indices]
    current_parallel_times = [parallel_times[i] for i in thread_indices]

     # Scatter plots
    axs[i].scatter(current_vectorsizes, current_sequential_times, label='Sequential', color='blue', marker='o', alpha=0.5)
    axs[i].scatter(current_vectorsizes, current_parallel_times, label='Parallel', color='red', marker='o', alpha=0.5)

    # Polynomial fit
    sequential_trendline = np.poly1d(np.polyfit(current_vectorsizes, current_sequential_times, 2))
    parallel_trendline = np.poly1d(np.polyfit(current_vectorsizes, current_parallel_times, 1))

    # Plot trendlines
    axs[i].plot(current_vectorsizes, sequential_trendline(current_vectorsizes), linestyle='-', color='black', linewidth=2)
    axs[i].plot(current_vectorsizes, parallel_trendline(current_vectorsizes), linestyle='-', color='black', linewidth=2)

    # Intersection point
    intersection_x = np.roots(sequential_trendline - parallel_trendline)[-1]
    intersection_y = sequential_trendline(intersection_x)
    if (intersection_x < max(current_vectorsizes)):
        axs[i].plot(intersection_x, intersection_y, marker='o', markersize=10, color='yellow', alpha=0.9, label=f'Intersection: ({intersection_x:.2f}, {intersection_y:.2f})', linestyle='None')

    ax2 = axs[i].twinx()
    ax2.set_ylabel(f'{thread_size} Threads')
    ax2.set_yticks([])
    ax2.set_yticklabels([])

    axs[i].set_ylabel('Time (μs)')
    axs[i].set_yscale('log')
    axs[i].grid(True)
    axs[i].legend(loc='upper right')

axs[0].set_title('Vector Size vs. Time for Sequential and Parallel Execution')
axs[-1].set_xlabel('Vector Size')

plt.show()
