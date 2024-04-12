import sys
sys.setrecursionlimit(100000)

res = 0


def top_sort(v: int):
    global p, idx, used
    used[v] = 1
    for to in g[v]:
        if used[to] == 0:
            top_sort(to)
    p[idx] = v + 1
    idx -= 1


def dfs(v: int):
    global res
    used[v] = 1
    for to in g[v]:
        if used[to] == 0:
            dfs(to)
        if used[to] == 1:
            res = -1
    used[v] = 2


n, m = map(int, input().split())

used = [0 for _ in range(n)]
path = []
g = [[] for _ in range(n)]
p = [0 for i in range(n)]
idx = n - 1
for i in range(m):
    u, v = map(int, input().split())
    g[u - 1].append(v - 1)

dfs(0)
if res == -1:
    print(-1)
else:
    used = [0 for _ in range(n)]
    for i in range(len(g)):
        if used[i] == 0:
            top_sort(i)
    if 0 not in p:
    	print(-1)
    else:
    	print(*p)
