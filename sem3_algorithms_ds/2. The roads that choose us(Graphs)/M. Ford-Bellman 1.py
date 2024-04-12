n, m = map(int, input().split())

minimums = [1e9 for _ in range(n + 1)]
minimums[1] = 0
for i in range(m):
    v, to, w = map(int, input().split())
    if minimums[v] != 1e9 and minimums[to] > minimums[v] + w:
        minimums[to] = minimums[v] + w

for i in range(1, n + 1):
    if minimums[i] > 30000:
        print(30000, end=' ')
    else:
        print(minimums[i], end=' ')
