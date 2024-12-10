import numpy as np

arr = np.array([1, 5, 2, -3, -5, 6, 8, 3, 3, 5, 4, 1, -5, 0, 2])
arr[(3 < arr) & (arr < 8)] *= -1
print(arr)