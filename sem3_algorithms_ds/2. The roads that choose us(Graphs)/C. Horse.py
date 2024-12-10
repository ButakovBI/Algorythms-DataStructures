K, N, j, i, m, s = map(int, input().split())
j -= 1
i -= 1
m -= 1
s -= 1
used = [[False for _ in range(N)] for _ in range(K)]


def bfs(j, i):
    used[j][i] = True

    if i - 1 >= 0 and j - 2 >= 0:
        if not used[j - 2][i - 1]:
            bfs(j - 2, i - 1)

    if i + 1 < N and j - 2 >= 0:
        if not used[j - 2][i + 1]:
            bfs(j - 2, i + 1)

    if i - 2 >= 0 and j - 1 >= 0:
        if not used[j - 1][i - 2]:
            bfs(j - 1, i - 2)

    if i + 2 < N and j - 1 >= 0:
        if not used[j - 1][i + 2]:
            bfs(j - 1, i + 2)

    if i - 1 >= 0 and j - 2 >= 0:
        if not used[j - 2][i - 1]:
            bfs(j - 2, i - 1)

    if i + 1 < N and j + 2 < K:
        if not used[j + 2][i + 1]:
            bfs(j + 2, i + 1)

    if i - 2 >= 0 and j + 1 < K:
        if not used[j + 1][i - 2]:
            bfs(j + 1, i - 2)

    if i + 2 < N and j + 1 < K:
        if not used[j + 1][i + 2]:
            bfs(j + 1, i + 2)


bfs(j, i)
if used[m][s]:
    print("YES")
else:
    print("NO")

