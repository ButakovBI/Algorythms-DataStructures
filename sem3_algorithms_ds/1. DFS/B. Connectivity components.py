def dfs1(v):
    used[v] = 1
    for to in g[v]:
        if not used[to]:
            dfs1(to)
    top.append(v)

def dfs2(v, c):
    color[v] = c
    repr[c] = v
    for to in gr[v]:
        if color[to] == -1:
            dfs2(to, c)

n = int(input())
g = [[] for _ in range(n + 1)]
gr = [[] for _ in range(n + 1)]

for _ in range(m):
    a, b = map(int, input().split())
    g[a].append(b)
    gr[b].append(a)

used = [0] * (n + 1)
top = []
color = [-1] * (n + 1)
repr = [-1] * (n + 1)

for i in range(1, n + 1):
    if not used[i]:
        dfs1(i)

top.reverse()

c = 0
for v in top:
    if color[v] == -1:
        dfs2(v, c)
        c += 1

used = [1] * c

for i in range(1, n + 1):
    for to in g[i]:
        if color[i] != color[to]:
            used[color[i]] = 0

count = sum(used)

print(count)
for i in range(c):
    if used[i]:
        print(repr[i], end=' ')
print()