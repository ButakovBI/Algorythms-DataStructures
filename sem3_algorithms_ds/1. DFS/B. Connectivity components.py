import sys

sys.setrecursionlimit(200000)
used = []
g = []
path = []
ans = []


def dfs(v: int, component: int) -> None:
    global path, ans, used
    used[v] = True
    components[v] = component
    path.append(v)
    for to in g[v]:
        if not used[to]:
            dfs(to, component)
    if len(path) > len(ans):
        ans = path[:]
    path.pop()


cnt = 0
n, m = map(int, input().split())
used = [False for i in range(n)]
g = [[] for i in range(n)]
components = [0 for i in range(n)]
for i in range(m):
    u, v = map(int, input().split())
    g[v - 1].append(u - 1)
    g[u - 1].append(v - 1)

for i in range(n):
    if not used[i]:
        cnt += 1
        dfs(i, cnt)

print(cnt)
print(*components)