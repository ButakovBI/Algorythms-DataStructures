n, m, start = map(int, input().split())
g = [[] for _ in range(n + 1)]
for i in range(m):
    u, v = map(int, input().split())
    g[u].append(v)
    g[v].append(u)

used = [False for _ in range(n + 1)]
used[start] = True
q = [start]
ans = [start]

while q:
    for to in g[q.pop(0)]:
        if not used[to]:
            used[to] = True
            q.append(to)
            ans.append(to)

print(len(ans))
print(*ans)
