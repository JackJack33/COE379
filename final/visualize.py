import numpy as np
import matplotlib.pyplot as plt

colors = []
with open("output.txt", "r") as file:
    lines = file.readlines()

for line in lines:
    color_str = line.split(": ")[1].strip()
    rgb = tuple(map(int, color_str[1:-1].split(", ")))
    colors.append(rgb)

lastline = lines[-1]
width = int(lastline.split("[")[1].split("]")[0]) + 1
height = int(lastline.split("[")[2].split("]")[0]) + 1

matplotlib_colors = np.zeros((height, width, 3), dtype=np.uint8)
for i, color in enumerate(colors):
    x = i % width
    y = i // width
    matplotlib_colors[y][x] = color

plt.figure(figsize=(width, height))
plt.imshow(matplotlib_colors, origin='lower')
plt.axis('off')
plt.show()
