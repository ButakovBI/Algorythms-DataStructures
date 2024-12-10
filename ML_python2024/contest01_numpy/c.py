import numpy as np

with open('input.txt') as f:
    vectors = np.array([list(map(float, line.split())) for line in f.readlines()])

norms = np.linalg.norm(vectors, axis=1)
non_zero_norms = norms != 0

non_zero_vectors = vectors[non_zero_norms]
non_zero_norms = norms[non_zero_norms]

if len(non_zero_vectors) < 2:
    print('No solution')
else:
    normalized_vectors = non_zero_vectors / non_zero_norms[:, None]
    cos_sim_matrix = np.dot(normalized_vectors, normalized_vectors.T)

    i_upper = np.triu_indices(cos_sim_matrix.shape[0], k=1)
    cos_sim = cos_sim_matrix[i_upper]

    res = np.min(cos_sim)
    if res == -np.inf:
        print("No solution")
    else:
         print(round(res, 2))
    
   
