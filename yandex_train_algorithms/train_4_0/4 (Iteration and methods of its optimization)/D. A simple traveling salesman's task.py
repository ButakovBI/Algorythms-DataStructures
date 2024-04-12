n = int(input())
graph = [list(map(int, input().split())) for _ in range(n)]

def tsp_dp(graph):
    n = len(graph)
    VISITED_ALL = (1 << n) - 1
    dp = [[None] * (1 << n) for _ in range(n)]

    def tsp(mask, pos):
        if mask == VISITED_ALL:
            return graph[pos][0] if graph[pos][0] > 0 else float('inf')

        if dp[pos][mask] is not None:
            return dp[pos][mask]

        ans = float('inf')
        for city in range(n):
            if (mask >> city) & 1 == 0 and graph[pos][city] > 0:
                new_mask = mask | (1 << city)
                new_dist = graph[pos][city] + tsp(new_mask, city)
                ans = min(ans, new_dist)

        dp[pos][mask] = ans
        return ans

    return tsp(1, 0)

result = tsp_dp(graph)
if n == 1:
    print(0)
else:
    print(result if result != float('inf') else -1)