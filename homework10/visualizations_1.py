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


fig, axs = plt.subplots(1,len(files))
cmap = colormaps['rainbow']

for i, file_data in data.items():
    unique_threads = sorted(set(data[i]['threads']))
    for j, thread in enumerate(unique_threads):
        thread_indices = [k for k, t in enumerate(file_data['threads']) if t == thread]
        color = cmap(1 - j / len(unique_threads))
        axs[i].plot([file_data['sizes'][k] for k in thread_indices], [file_data['times'][k] for k in thread_indices], marker='o', color=color, label=f"{thread} threads")
    axs[i].set_xscale('log')
    axs[i].set_yscale('log')
    axs[i].set_title(f'Time vs. Size - {files[i]}')
    axs[i].grid(True)

axs[0].set_ylabel('Time (s)')
axs[int(len(axs)/2)].set_xlabel('Size')

plt.show()
