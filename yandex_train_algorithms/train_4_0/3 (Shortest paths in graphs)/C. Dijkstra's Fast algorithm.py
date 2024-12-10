import heapq


def main():
    n, k = map(int, input().split())
    g = [[] for _ in range(n + 1)]
    for i in range(k):
        a, b, l = map(int, input().split())
        g[a].append((b, l))
        g[b].append((a, l))
    s, f = map(int, input().split())
    dist = [1e18] * (n + 1)
    dist[s] = 0
    pq = [(s, 0)]
    while pq:
        cur_v, cur_length = heapq.heappop(pq)
        if dist[cur_v] == 1e18 or cur_length > dist[cur_v]:
            continue
        for to, w in g[cur_v]:
            if dist[to] > dist[cur_v] + w:
                dist[to] = dist[cur_v] + w
                pq.append((to, dist[to]))

    if dist[f] == 1e18:
        print(-1)
    else:
        print(dist[f])


if __name__ == '__main__':
    main()
