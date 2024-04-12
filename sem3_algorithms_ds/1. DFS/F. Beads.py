import sys

sys.setrecursionlimit(100000)
used = []
g = []
path = []
ans = []

res = "YES"


def dfs(v: int) -> None:
    global path, ans, used, res
    used[v] = True
    path.append(v)
    for to in g[v]:
        if not used[to]:
            dfs(to)
    if len(ans) < len(path):
        ans = path[:]
    path.pop()


n = int(input())

used = [False for i in range(n + 1)]
g = [[] for i in range(n + 1)]
for i in range(n - 1):
    u, v = map(int, input().split())
    g[v].append(u)
    g[u].append(v)

dfs(1)
used = [False for i in range(n + 1)]
dfs(ans[-1])
print(len(ans))
