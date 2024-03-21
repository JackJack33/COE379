import matplotlib.pyplot as plt
import numpy as np

from matplotlib import colormaps

threads = []
sizes = []
iterations = []
precision = []
times = []

with open('times.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        threads.append(int(data[0]))
        sizes.append(int(data[1]))
        iterations.append(int(data[2]))
        precision.append(float(data[3]))
        times.append(float(data[4]))

unique_threads = sorted(set(threads))
cmap = colormaps['rainbow']
plt.figure(figsize=(10, 5))

plt.subplot(1, 3, 1)
for i, thread in enumerate(unique_threads):
    thread_indices = [j for j, t in enumerate(threads) if t == thread]
    color = cmap(1 - i / len(unique_threads))
    plt.plot([sizes[j] for j in thread_indices], [times[j] for j in thread_indices], marker='o', color=color, label=f"{thread} threads")
plt.xscale('log')
plt.xlabel('Size')
plt.ylabel('Time')
plt.title('Time vs. Size')
plt.legend()
plt.grid(True)

plt.subplot(1, 3, 2)
for i, thread in enumerate(unique_threads):
    thread_indices = [j for j, t in enumerate(threads) if t == thread]
    color = cmap(i / len(unique_threads))  # Get color from the colormap
    plt.plot([sizes[j] for j in thread_indices], [precision[j] for j in thread_indices], color=color, linewidth=(20 * (1 - i / len(unique_threads))), label=f"{thread} threads")
plt.xscale('log')
plt.xlabel('Size')
plt.ylabel('Precision')
plt.title('Precision vs. Size')
plt.legend()
plt.grid(True)

plt.subplot(1, 3, 3)
for i, thread in enumerate(unique_threads):
    thread_indices = [j for j, t in enumerate(threads) if t == thread]
    color = cmap(i / len(unique_threads))  # Get color from the colormap
    plt.plot([sizes[j] for j in thread_indices], [iterations[j] for j in thread_indices], color=color, linewidth=(20 * (1 - i / len(unique_threads))), label=f"{thread} threads")
plt.xscale('log')
plt.xlabel('Size')
plt.ylabel('Iterations')
plt.title('Iterations vs. Size')
plt.legend()
plt.grid(True)

plt.grid(True)
plt.show()
