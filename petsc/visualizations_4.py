import matplotlib.pyplot as plt
import numpy as np

names = []
pcsetup = []
flops_sec = []
matmult_iter = []

with open('cost.txt', 'r') as file:
    # skip header
    next(file)
    for line in file:
        data = line.strip().split()
        names.append(data[0] + "," + data[1] + "," + data[2])
        pcsetup.append(float(data[3]))
        flops_sec.append(float(data[4]))
        matmult_iter.append(float(data[5]) / float(data[6]))


plt.figure(figsize=(10, 5))


#bars = plt.bar(names, pcsetup, color='skyblue')
#plt.ylabel('PCSetUp Time (s)')
#plt.title('PCSetUp Time for Different Configurations')

#bars = plt.bar(names, flops_sec, color='salmon')
#plt.ylabel('Flops/Sec')
#plt.title('Flops/Sec for Different Configurations')

bars = plt.bar(names, matmult_iter, color='lightgreen')
plt.ylabel('MatMult / Iterations')
plt.title('Matrix/Vector Products Per Iteration for Different Configurations')


plt.xticks([])
max_height = max(bar.get_height() for bar in bars)
annotation_height = max_height / 2
for i, bar in enumerate(bars):
    plt.text(bar.get_x() + bar.get_width() / 2, annotation_height, names[i],
             ha='center', va='bottom', rotation=45)

plt.legend()
plt.grid()
plt.show()




