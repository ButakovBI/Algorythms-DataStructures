import sys

sys.setrecursionlimit(10000)
used = []
g = []
path = []
ans = []


def dfs(v: int) -> None:
    global path, ans, used
    used[v] = True
    path.append(v)
    for to in g[v]:
        if not used[to]:
            dfs(to)
    if len(path) > len(ans):
        ans = path[:]
    path.pop()


n, m = map(int, input().split())
used = [False for i in range(n)]
g = [[] for i in range(n)]
for i in range(m):
    u, v = map(int, input().split())
    g[v - 1].append(u - 1)
    g[u - 1].append(v - 1)


dfs(1)
if False in used:
    print("NO")
else:
    print("YES")