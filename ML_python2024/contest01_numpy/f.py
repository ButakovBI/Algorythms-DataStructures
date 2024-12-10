import numpy as np

matrix = []
while True:
    try:
        row = input().strip()
        if not row:
            break
        matrix.append(list(map(float, row.split())))
    except EOFError:
        break

matrix = np.array(matrix)
row_means = matrix.mean(axis=1).reshape(-1, 1)
res = matrix - row_means

print(str(res))
