import numpy as np

with open("input.txt", "r") as file:
    data = file.read()

data = data.replace('[', '').replace(']', '').split()
pixels = list(map(int, data))

array = np.array(pixels).reshape(-1, 3)
unique_colors = np.unique(array, axis=0)
print(len(unique_colors))

for color in unique_colors:
    print(*color)
