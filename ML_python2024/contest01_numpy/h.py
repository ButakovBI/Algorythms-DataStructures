import numpy as np
import matplotlib.pyplot as plt
from scipy.ndimage import rotate
import re

with open("input.txt", "r") as file:
    angle = int(file.readline().strip())
    data = file.read()

data_with_commas = re.sub(r'(\d)\s+(\d)', r'\1, \2', data)
data_with_commas = re.sub(r'\]\s+\[', '], [', data_with_commas)
data_with_commas = re.sub(r'(\d)\s+(\d)', r'\1, \2', data_with_commas)
arr = np.array(eval(data_with_commas))
plt.imshow(arr)
plt.show()
print(angle)
rotated_array = rotate(arr, angle, reshape=True, order=0, mode='constant', cval=0)
print(rotated_array)
plt.imshow(rotated_array)
plt.show()
