import numpy as np
import matplotlib.pyplot as plt

height, width = map(int, input().split())
square_color = tuple(map(int, input().split()))
border_color = tuple(map(int, input().split()))

image = np.zeros((height, width, 3), dtype=int)

image[:2, :, :] = border_color
image[-2:, :, :] = border_color
image[:, :2, :] = border_color
image[:, -2:, :] = border_color
image[2:-2, 2:-2, :] = square_color

print(image)
