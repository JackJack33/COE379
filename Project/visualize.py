import numpy as np
from PIL import Image

colors = []
with open("build/output.txt", "r") as file:
    lines = file.readlines()

print("Read file, rendering...")

for line in lines:
    color_str = line.split(": ")[1].strip()
    rgb = tuple(map(int, color_str[1:-1].split(", ")))
    colors.append(rgb)

lastline = lines[-1]
width = int(lastline.split("[")[1].split("]")[0]) + 1
height = int(lastline.split("[")[2].split("]")[0]) + 1

ordered_colors = np.zeros((height, width, 3), dtype=np.uint8)
for i, color in enumerate(colors):
    x = i % width
    y = i // width
    ordered_colors[y][x] = color

image = Image.fromarray(ordered_colors, "RGB")
image.save("output.png")
print("Done. Exported to output.png")
