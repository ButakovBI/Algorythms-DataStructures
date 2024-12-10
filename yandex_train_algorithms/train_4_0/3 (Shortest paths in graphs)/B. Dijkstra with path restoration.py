import heapq


def main():
    n, s, f = map(int, input().split())
    g = [[] for _ in range(n + 1)]
    for i in range(1, n + 1):
        numbers = list(map(int, input().split()))
        for j in range(n):
            if numbers[j] != -1:
                g[i].append((j + 1, numbers[j]))
    dist = [1e9] * (n + 1)
    path = [0] * (n + 1)
    dist[s] = 0
    pq = [s]
    while pq:
        cur_v = heapq.heappop(pq)
        if dist[cur_v] == 1e9:
            continue
        for to, w in g[cur_v]:
            if dist[to] > dist[cur_v] + w:
                dist[to] = dist[cur_v] + w
                heapq.heappush(pq, to)
                path[to] = cur_v

    if dist[f] == 1e9:
        print(-1)
    else:
        vertex = f
        ans = [f]
        while vertex != s:
            ans.append(path[vertex])
            vertex = path[vertex]
        print(*reversed(ans))


if __name__ == '__main__':
    main()
