import sys
sys.setrecursionlimit(100000)
from copy import deepcopy

max_count_v = 0

def dfs(v: int):
    global cur_path, max_count_v
    used[v] = 1
    for to in g[v]:
        if used[to] == 0:
            count[to] += count[v] + 1
            if count[to] > max_count_v:
                max_count_v = count[to]
            dfs(to)


n = int(input())
if n == 1:
    print(0, 1, 1)
else:
    used = [0 for _ in range(n + 1)]
    g = [[] for _ in range(n + 1)]
    count = [0 for _ in range(n + 1)]

    for i in range(n - 1):
        u, v = map(int, input().split())
        g[u].append(v)
        g[v].append(u)

    dfs(1)
    max_length_v = count.index(max(count))

    used = [0 for _ in range(n + 1)]
    count = [0 for _ in range(n + 1)]
    max_count_v = 0
    dfs(max_length_v)
    max_length = max(count)
    print(max_length // 2 + max_length % 2, end=' ')
    if max_length % 2:
        print(2, *sorted([count[1:].index(max_length // 2) + 1, count[1:].index(max_length // 2 + 1) + 1]))
    else:
        print(1, count[1:].index(max_length // 2) + 1)




# 11
# 1 2
# 1 3
# 3 4
# 3 5
# 5 6
# 6 7
# 1 8
# 8 9
# 9 10
# 10 11
