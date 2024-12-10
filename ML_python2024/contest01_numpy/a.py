import numpy as np

height, width = map(int, input().split())

arr = np.zeros((height, width), dtype=int)
arr[1::2,::2] = 255
arr[::2, 1::2] = 255

print(arr)
