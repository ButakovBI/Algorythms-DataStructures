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

print(sum(matrix[::, i].sum() == 0 for i in range(matrix.shape[1])))
