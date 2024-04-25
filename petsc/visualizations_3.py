import matplotlib.pyplot as plt
import numpy as np

vectorsize = []
cg_times = []
bcgs_times = []
gmres_times = []

with open('times_cg.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        vectorsize.append(float(data[0]))
        cg_times.append(int(data[1]))

with open('times_uns_05_cg.txt', 'r') as file:
    # skip header
    next(file)
    idx = 0
    for line in file:
        data = line.strip().split()
        cg_times[idx] -= (int(data[1]))
        idx+=1

with open('times_bcgs.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        bcgs_times.append(int(data[1]))

with open('times_uns_05_bcgs.txt', 'r') as file:
    # skip header
    next(file)
    idx = 0
    for line in file:
        data = line.strip().split()
        bcgs_times[idx] -= (int(data[1]))
        idx+=1

with open('times_gmres.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        gmres_times.append(int(data[1]))

with open('times_uns_05_gmres.txt', 'r') as file:
    # skip header
    next(file)
    idx = 0
    for line in file:
        data = line.strip().split()
        gmres_times[idx] -= (int(data[1]))
        idx+=1

plt.plot(vectorsize, cg_times, marker='o', label='CG')
plt.plot(vectorsize, bcgs_times, marker='o', label='BCGS')
plt.plot(vectorsize, gmres_times, marker='o', label='GMRES')
plt.xlabel('Vector Size')
plt.ylabel('Signed Iteration Difference')
plt.title('Vector Size vs. Signed Iteration Difference (Default - Unsymmetry=0.5)')
plt.legend()
plt.grid()
plt.show()




