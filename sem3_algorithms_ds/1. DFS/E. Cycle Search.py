import sys
sys.setrecursionlimit(100000)


def dfs(v: int):
    used[v] = 1
    path.append(v)
    for to in g[v]:
        if used[to] == 0:
            dfs(to)
        if used[to] == 1:
            print("YES")
            print(*path[path.index(to):])
            exit()
    used[v] = 2
    path.pop()


n, m = map(int, input().split())

used = [0 for _ in range(n + 1)]
path = []
g = [[] for _ in range(n + 1)]
for i in range(m):
    u, v = map(int, input().split())
    g[u].append(v)

for i in range(1, n + 1):
    dfs(i)

print("NO")
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
