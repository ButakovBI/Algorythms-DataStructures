n, m = map(int, input().split())
g = [[] for _ in range(n + 1)]

for i in range(m):
    u, v = map(int, input().split())
    g[u].append(v)
    g[v].append(u)

colors = [-1] * (n + 1)

def dfs(v, color):
    colors[v] = color
    for to in g[v]:
        if colors[to] == -1:
            if not dfs(to, 1 - color):
                return False
        elif colors[to] == color:
            return False
    return True

for i in range(1, n + 1):
    if colors[i] == -1:
        if not dfs(i, 0):
            print("NO")
            break
else:
    print("YES")