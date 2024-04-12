import sys

sys.setrecursionlimit(100000)
used = []
g = []
path = []
ans = []

res = []


def dfs(v: int) -> None:
    global path, ans, used
    used[v] = True
    path.append(v)
    for to in g[v]:
        if not used[to]:
            dfs(to)
            path.append(v)



cnt = 0
n, m, V = map(int, input().split())
used = [False for i in range(n + 1)]
g = [[] for i in range(n + 1)]
for i in range(m):
    u, v = map(int, input().split())
    g[v].append(u)
    g[u].append(v)
dfs(V)
print(len(path))
print(*path)


