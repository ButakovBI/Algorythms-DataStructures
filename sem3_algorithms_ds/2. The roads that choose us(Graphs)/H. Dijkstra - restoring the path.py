n, s, f = map(int, input().split())

d = [[0 for _ in range(n)] for _ in range(n)]
g = [[] for _ in range(n)]
path = [0 for _ in range(n)]
lengths = [1e9 for _ in range(n)]

for i in range(n):
    numbers = list(map(int, input().split()))
    for j in range(n):
        d[i][j] = numbers[j]
        if j != i and numbers[j] != -1:
            g[i].append(j)


lengths[s - 1] = 0
used = [False for _ in range(n)]
min_elem = 1e9 + 1
while min_elem != 1e9:
    min_elem = 1e9
    min_idx = -1
    for i in range(n):
        if not used[i] and lengths[i] < min_elem:
            min_elem = lengths[i]
            min_idx = i
    used[min_idx] = True
    for to in g[min_idx]:
        if lengths[to] > lengths[min_idx] + d[min_idx][to]:
            lengths[to] = lengths[min_idx] + d[min_idx][to]
            path[to] = min_idx

if lengths[f - 1] == 1e9:
    print(-1)
else:
    ans = [f]
    while ans[-1] != s:
        ans.append(path[ans[-1] - 1] + 1)
    print(*list(reversed(ans)))
