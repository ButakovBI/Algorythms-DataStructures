import heapq

n, m = map(int, input().split())

cities = list(map(int, input().split()))
g = [[] for _ in range(n)]
used = [False for _ in range(n)]

for i in range(m):
    u, v = map(int, input().split())
    g[u - 1].append(v - 1)
    g[v - 1].append(u - 1)


lengths = [1e9 for _ in range(n)]
lengths[0] = 0
pq = [(0, 0)]
path = [0 for _ in range(n)]
path[0] = 0

while pq:
    v, cur_length = heapq.heappop(pq)
    if lengths[v] < cur_length:
        continue
    for to in g[v]:
        if lengths[to] > lengths[v] + (cities[to] != cities[v]):
            lengths[to] = lengths[v] + (cities[to] != cities[v])
            path[to] = v
            heapq.heappush(pq, (to, lengths[to]))


if lengths[-1] == 1e9:
    print('impossible')
else:
    ans = [n]
    while ans[-1] != 1:
        ans.append(path[ans[-1] - 1] + 1)
    print(lengths[-1], len(ans))
    print(*list(reversed(ans)))
