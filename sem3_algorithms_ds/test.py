n, m = map(int, input().split())
s, e = map(int, input().split())

d = []
for i in range(n):
    d.append(list(map(int, input().split())))

for k in range(n):
    for i in range(n):
        for j in range(n):
            d[i][j] = min(d[i][j], d[i][k] + d[k][j])

for row in d:
    print(*row)