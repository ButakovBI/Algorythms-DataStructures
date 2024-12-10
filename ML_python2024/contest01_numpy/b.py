import numpy as np

k = int(input())

matrix = []
try:
    while True:
        line = input().strip()
        if line:
            matrix.append(list(map(int, line.split())))
except EOFError:
    pass

matrix = np.array(matrix)
n_rows, n_cols = matrix.shape
block_rows = (n_rows + k - 1) // k
block_cols = (n_cols + k - 1) // k

res = np.zeros((block_rows, block_cols), dtype=int)

res = np.array([
    [np.sum(matrix[i*k:min((i+1)*k, n_rows), j*k:min((j+1)*k, n_cols)])
     for j in range(block_cols)]
    for i in range(block_rows)
])

for i in range(block_rows):
    print(*res[i])



