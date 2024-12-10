import sys

sys.setrecursionlimit(10000000)

n = int(input())
ans = 0
used = [0 for _ in range(n + 1)]
gr = [[] for _ in range(n + 1)]
root = -1
for i in range(1, n + 1):
    m = int(input())
    gr[m].append(i)
    gr[i].append(m)
    if m == 0:
        root = i

colors = [0 for _ in range(n + 1)]


def dfs(v: int, p: int = 0):
    used[v] = 1
    flag = 1
    if len(gr[v]) < 2 and p != 0:
        colors[v] = 1
    else:
        for to in gr[v]:
            if to == p:
                continue
            if not used[to]:
                dfs(to, v)
                if colors[to] == 1:
                    flag = 0
        if flag == 1:
            colors[v] = 1


dfs(root)
print(sum(colors[1:]))

# 10
# 0
# 1
# 1
# 2
# 2
# 2
# 3
# 3
# 3
# 3

# 29
# 0
# 1
# 2
# 2
# 4
# 4
# 3
# 3
# 3
# 1
# 10
# 10
# 12
# 10
# 1
# 5
# 5
# 15
# 1
# 18
# 18
# 18
# 17
# 8
# 13
# 14
# 14
# 26
# 11
