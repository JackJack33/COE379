import matplotlib.pyplot as plt
import numpy as np

from matplotlib import colormaps

data = {}
files = ['times_3.txt', 'times_4.txt', 'times_5.txt']

for i, filename in enumerate(files):
    data[i] = {'threads': [], 'sizes': [], 'iterations': [], 'precision': [], 'times': []}
    with open(filename, 'r') as file:
        # skip header
        next(file)
        for line in file:
            values = line.strip().split()
            data[i]['threads'].append(int(values[0]))
            data[i]['sizes'].append(int(values[1]))
            data[i]['iterations'].append(int(values[2]))
            data[i]['precision'].append(float(values[3]))
            data[i]['times'].append(float(values[4]))


fig, ax = plt.subplots(1, 1)
cmap = colormaps['rainbow']
unique_threads = sorted(set(data[0]['threads']))

for j, thread in enumerate(unique_threads):
    thread_indices = [k for k, t in enumerate(data[0]['threads']) if t == thread]
    color = cmap(1 - j / len(unique_threads))
    ax.plot([data[0]['sizes'][k] for k in thread_indices], [(data[0]['times'][k] - data[1]['times'][k]) for k in thread_indices], marker='o', color=color, label=f"{thread} threads")

ax.set_xlabel('Size')
ax.set_xscale('log')
ax.set_ylabel('Time Difference (s)')
ax.set_title('Difference in Time between times_3.txt and times_4.txt')
ax.legend()
ax.legend(loc='lower left')
ax.grid(True)

plt.show()
