import matplotlib.pyplot as plt
import numpy as np

threads_100 = []
times_100 = []
threads_25 = []
times_25 = []

with open('times_100.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        threads_100.append(int(data[0]))
        times_100.append(float(data[1]))

with open('times_25.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        threads_25.append(int(data[0]))
        times_25.append(float(data[1]))

plt.figure()

plt.plot(threads_100, times_100, marker='o', label='100 Iterations')
plt.plot(threads_25, times_25, marker='o', label='25 Iterations')
plt.xlabel('Threads')
plt.ylabel('Time')
plt.title('Time vs. Threads')
plt.legend()
plt.grid(True)

plt.grid(True)
plt.show()
