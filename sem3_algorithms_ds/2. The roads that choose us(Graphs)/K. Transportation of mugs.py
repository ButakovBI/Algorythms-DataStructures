import heapq


def dijkstra(mid, g, n):
    summary_weight = 3000000 + mid * 100
    time = [1e9 + 1 for _ in range(n)]
    time[0] = 0
    pq = [(0, 0)]
    while pq:
        v, cur_time = heapq.heappop(pq)
        if cur_time > time[v]:
            continue
        for to, mins, weight in g[v]:
            if summary_weight <= weight and time[v] + mins < time[to]:
                time[to] = time[v] + mins
                heapq.heappush(pq, (to, time[to]))
    return time[n - 1] <= 1440


n, m = map(int, input().split())

g = [[] for _ in range(n)]


for i in range(m):
    u, v, minute, weight = map(int, input().split())
    g[u - 1].append((v - 1, minute, weight))
    g[v - 1].append((u - 1, minute, weight))

l, r, ans = 0, 1e7, 0
while l <= r:
    mid = (l + r) // 2
    if dijkstra(mid, g, n):
        ans = mid
        l = mid + 1
    else:
        r = mid - 1

print(int(ans))

# to C++