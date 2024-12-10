n = int(input())

d = [[1e9 for _ in range(n)] for _ in range(n)]
for i in range(n):
    numbers = list(map(int, input().split()))
    for j in range(n):
        if numbers[j] != -1:
            d[i][j] =numbers[j]

for k in range(n):
    for i in range(n):
        for j in range(n):
            d[i][j] = min(d[i][j], d[i][k] + d[k][j])

diam = -1e9
r = 1e9
for row in d:
    diam = max(diam, max(row))
    r = min(max(row), r)
print(diam, r, sep='\n')