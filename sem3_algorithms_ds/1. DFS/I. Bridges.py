import sys

sys.setrecursionlimit(20000000)

n, m = map(int, input().split())
used = [False for _ in range(n + 1)]
g = [[] for _ in range(n + 1)]
tin = [0 for _ in range(n + 1)]
up = [0 for _ in range(n + 1)]
ans = []
cnt = 0

d = dict()

for i in range(m):
    u, v = map(int, input().split())
    d[f"{min(u, v)},{max(u, v)}"] = i + 1
    g[u].append(v)
    g[v].append(u)


def dfs(v: int, p: int = -1):
    global cnt
    used[v] = True
    cnt += 1
    tin[v] = cnt
    up[v] = cnt
    for to in g[v]:
        if to == p:
            continue
        if not used[to]:
            dfs(to, v)
            up[v] = min(up[v], up[to])
            if tin[v] < up[to]:
                ans.append((v, to))
        else:
            up[v] = min(up[v], tin[to])



for i in range(1, n + 1):
    if not used[i]:
        dfs(i)

ans.sort()
print(len(ans))
res = []
for u, v in ans:
    res.append(d[f"{min(u, v)},{max(u, v)}"])
print(*sorted(res))


# 9 11
# 1 2
# 2 3
# 1 7
# 7 8
# 1 3
# 8 9
# 9 7
# 4 6
# 5 6
# 5 4
# 4 3

# 12 15
# 1 2
# 2 6
# 6 7
# 10 7
# 12 10
# 11 12
# 11 10
# 9 7
# 7 8
# 9 8
# 2 3
# 3 4
# 5 3
# 5 4
# 1 6