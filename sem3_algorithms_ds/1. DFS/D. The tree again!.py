import sys
sys.setrecursionlimit(100000)

res = "YES"


def dfs(v: int, parent: int):
    global res
    used[v] = 1
    if v in path:
        res = "NO"
    path.append(v)
    for to in g[v]:
        if used[to] == 0:
            dfs(to, v)
        elif to != parent:
            res = "NO"


n, m = map(int, input().split())

used = [0 for _ in range(n + 1)]
path = []
g = [[] for _ in range(n + 1)]
for i in range(m):
    u, v = map(int, input().split())
    g[u].append(v)
    g[v].append(u)


dfs(1, 0)
if len(path) != n:
    res = "NO"
print(res)
# 11 14
# 1 2
# 1 3
# 3 4
# 3 5
# 5 6
# 6 7
# 7 5
# 1 8
# 8 9
# 9 10
# 10 11
# 11 9
# 7 10
# 9 5
