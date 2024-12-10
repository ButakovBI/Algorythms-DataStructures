import numpy as np

matrix = np.loadtxt('input.txt', dtype=int)

unique_rows = np.unique(matrix, axis=0)
print(len(unique_rows))
