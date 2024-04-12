import sys

sys.setrecursionlimit(100000)


def dfs(vertex: int, parent : int) -> None:
    global counter
    count_dfs = 0
    used[vertex] = 1
    counter += 1
    up[vertex] = counter
    tin[vertex] = counter
    for to in g[vertex]:
        if to == parent:
            continue
        if used[to] == 0:
            dfs(to, vertex)
            count_dfs += 1
            up[vertex] = min(up[vertex], up[to])
            if tin[vertex] <= up[to] and parent != -1:
                answer_array.append(vertex)
        else:
            up[vertex] = min(up[vertex], tin[to])
    if parent == -1 and count_dfs > 1:
        answer_array.append(vertex)


n, m = map(int, input().split())
n += 1
used = [0 for _ in range(n)]
g = [[] for _ in range(n)]
up = [0 for _ in range(n)]
tin = [0 for _ in range(n)]
answer_array = []
counter = 0

for edge in range(m):
    u, v = map(int, input().split())
    g[u].append(v)
    g[v].append(u)

dfs(1, -1)

answer_array = sorted(list(set(answer_array)))
print(len(answer_array))
print(*answer_array)