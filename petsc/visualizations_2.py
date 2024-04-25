import matplotlib.pyplot as plt
import numpy as np

unsymmetry = []
cg_times = []
bcgs_times = []
gmres_times = []

with open('times_uns_cg.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        unsymmetry.append(float(data[0]))
        cg_times.append(int(data[1]))

with open('times_uns_bcgs.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        bcgs_times.append(int(data[1]))

with open('times_uns_gmres.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        gmres_times.append(int(data[1]))

plt.plot(unsymmetry, cg_times, marker='o', label='CG')
plt.plot(unsymmetry, bcgs_times, marker='o', label='BCGS')
plt.plot(unsymmetry, gmres_times, marker='o', label='GMRES')
plt.xlabel('Unsymmetry')
plt.ylabel('Iterations')
plt.yscale('log')
plt.title('Unsymmetry vs. Iterations')
plt.legend()
plt.grid()
plt.show()




