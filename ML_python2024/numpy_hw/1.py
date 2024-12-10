import numpy as np

res = np.ones((10, 10))
res[1:-1, 1:-1] = 0
print(res)