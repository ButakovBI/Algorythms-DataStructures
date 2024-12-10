import heapq


def main():
    n = int(input())
    s, f = map(int, input().split())
    r = int(input())
    g = [[] for _ in range(n + 1)]
    for i in range(r):
        a, start, b, end = map(int, input().split())
        g[a].append((b, start, end))

    dist = [1e9] * (n + 1)
    dist[s] = 0
    time = [1e9] * (n + 1)
    time[s] = 0
    pq = [(s, 0, 0)]
    while pq:
        cur_v, cur_start, cur_end = heapq.heappop(pq)
        if cur_end - cur_start > time[cur_v]:
            continue
        for to, start, end in g[cur_v]:
            if cur_end <= start and time[to] > end:
                time[to] = end
                heapq.heappush(pq, (to, start, end))
    if time[f] == 1e9:
        print(-1)
    else:
        print(time[f])


if __name__ == '__main__':
    main()
