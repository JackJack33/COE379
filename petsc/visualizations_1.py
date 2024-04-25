import matplotlib.pyplot as plt
import numpy as np

vectorsizes = []
cg_times = []
bcgs_times = []
gmres_times = []

with open('times_cg.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        vectorsizes.append(int(data[0]))
        cg_times.append(int(data[1]))

with open('times_bcgs.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        bcgs_times.append(int(data[1]))

with open('times_gmres.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        gmres_times.append(int(data[1]))

plt.plot(vectorsizes, cg_times, marker='o', label='CG')
plt.plot(vectorsizes, bcgs_times, marker='o', label='BCGS')
plt.plot(vectorsizes, gmres_times, marker='o', label='GMRES')
plt.xlabel('Vector Sizes')
plt.ylabel('Iterations')
plt.yscale('log')
plt.title('Vector Sizes vs. Iterations')
plt.legend()
plt.grid()
plt.show()




